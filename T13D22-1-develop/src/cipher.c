#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define FILEPATH_MAX_LEN 1025

#include "log_levels.h"
#include "logger.h"

void use_menu_options(char *fpath, int option, int *error, FILE *logger);
void read_txt_file(char *fpath, int *error, FILE *logger);
void write_txt_file(char *fpath, int *error, FILE *logger);
void read_string_from_stdin(char *str);
void encode_cesar(int *error, FILE *logger);
void apply_cesar(int shift, FILE *fpointer);

int main() {
    int menu_option = 0;
    char filepath[FILEPATH_MAX_LEN] = {'\0'};
    FILE *logger = NULL;

#ifdef LOG
    char *logfile = "log.txt";
    logger = log_init(logfile);
#endif

    do {
        int error = 0;
        if (!scanf("%d", &menu_option)) {
            error = 1;
            if (logger) {
                logcat(logger, "Invalid menu option", ERROR);
            }
        }
        while (getchar() != '\n')
            ;

        if (!error) {
            use_menu_options(filepath, menu_option, &error, logger);
        }

        if (error) {
            printf("n/a");
            error = 0;
        }

        if (menu_option != -1) printf("\n");
    } while (menu_option != -1);

#ifdef LOG
    log_close(logger);
#endif

    return 0;
}

void use_menu_options(char *fpath, int option, int *error, FILE *logger) {
    if (option == 1)
        read_txt_file(fpath, error, logger);
    else if (option == 2)
        write_txt_file(fpath, error, logger);
    else if (option == 3)
        encode_cesar(error, logger);
    else if (option != -1) {
        *error = 1;
        if (logger) {
            logcat(logger, "Wrong menu option", ERROR);
        }
    }
}

void read_txt_file(char *fpath, int *error, FILE *logger) {
    read_string_from_stdin(fpath);
    FILE *fpointer = fopen(fpath, "r");
    if (fpointer == NULL) {
        *error = 1;
        if (logger) {
            char message[FILEPATH_MAX_LEN] = "File \"";
            strcat(message, fpath);
            strcat(message, "\" not found");
            logcat(logger, message, ERROR);
        }
    } else {
        if (logger) {
            char message[FILEPATH_MAX_LEN] = "File \"";
            strcat(message, fpath);
            strcat(message, "\" opened");
            logcat(logger, message, INFO);
        }

        char str[FILEPATH_MAX_LEN];
        if (fgets(str, FILEPATH_MAX_LEN - 1, fpointer) == NULL) {
            *error = 1;
            if (logger) {
                char message[FILEPATH_MAX_LEN] = "File \"";
                strcat(message, fpath);
                strcat(message, "\" is empty");
                logcat(logger, message, WARNING);
            }
        } else {
            do {
                printf("%s", str);
            } while (fgets(str, FILEPATH_MAX_LEN - 1, fpointer) != NULL);
        }
        fclose(fpointer);
        if (logger) {
            char message[FILEPATH_MAX_LEN] = "File \"";
            strcat(message, fpath);
            strcat(message, "\" closed");
            logcat(logger, message, INFO);
        }
    }
}

void write_txt_file(char *fpath, int *error, FILE *logger) {
    char str[FILEPATH_MAX_LEN] = {'\0'};
    FILE *fpointer = fopen(fpath, "r+");
    read_string_from_stdin(str);
    if (fpointer == NULL) {
        *error = 1;
        if (logger) {
            char message[FILEPATH_MAX_LEN] = "File \"";
            strcat(message, fpath);
            strcat(message, "\" not found");
            logcat(logger, message, ERROR);
        }
    } else {
        fseek(fpointer, 0, SEEK_END);
        fputs(str, fpointer);
        if (logger) {
            char message[FILEPATH_MAX_LEN] = "File \"";
            strcat(message, fpath);
            strcat(message, "\" modified. Appended string: ");
            strcat(message, str);
            logcat(logger, message, INFO);
        }
        rewind(fpointer);
        while (fgets(str, FILEPATH_MAX_LEN - 1, fpointer) != NULL) {
            printf("%s", str);
        }
        if (logger) {
            char message[FILEPATH_MAX_LEN] = "File \"";
            strcat(message, fpath);
            strcat(message, "\" closed");
            logcat(logger, message, INFO);
        }
        fclose(fpointer);
    }
}

void read_string_from_stdin(char *str) {
    int i = 0;
    char ch;
    do {
        ch = getchar();
        if (ch != '\n') str[i] = ch;
        i++;
    } while (ch != '\n' && i < FILEPATH_MAX_LEN - 1);
    str[i] = '\0';
}

void encode_cesar(int *error, FILE *logger) {
    int shift = 0;
    char dir[FILEPATH_MAX_LEN] = {'\0'};
    char ext[FILEPATH_MAX_LEN] = {'\0'};
    char buf[FILEPATH_MAX_LEN] = {'\0'};
    read_string_from_stdin(dir);

    struct dirent *in_file;
    DIR *dpointer = opendir(dir);

    if (!dpointer) {
        *error = 1;
        if (logger) {
            char message[FILEPATH_MAX_LEN] = "Directory \"";
            strcat(message, dir);
            strcat(message, "\" not found");
            logcat(logger, message, ERROR);
        }
    } else {
        if (!scanf("%d", &shift)) {
            *error = 1;
            if (logger) {
                char message[FILEPATH_MAX_LEN] = "Trying to input invalid shift value";
                logcat(logger, message, ERROR);
            }
        } else {
            getchar();
            while ((in_file = readdir(dpointer))) {
                if (!strcmp(in_file->d_name, ".")) continue;
                if (!strcmp(in_file->d_name, "..")) continue;

                strcpy(buf, in_file->d_name);
                char *lexeme = strtok(buf, ".");
                while (lexeme) {
                    strcpy(ext, lexeme);
                    lexeme = strtok(NULL, ".");
                }

                FILE *fpointer;
                strcpy(buf, dir);
                strcat(buf, in_file->d_name);

                if (!strcmp(ext, "c")) {
                    fpointer = fopen(buf, "r+");
                    if (logger) {
                        char message[FILEPATH_MAX_LEN] = "File \"";
                        strcat(message, buf);
                        strcat(message, "\" opened");
                        logcat(logger, message, INFO);
                    }
                    apply_cesar(shift, fpointer);
                    if (logger) {
                        char message[FILEPATH_MAX_LEN] = "File \"";
                        strcat(message, buf);
                        strcat(message, "\" encoded with Ceasar code");
                        logcat(logger, message, INFO);
                    }
                    fclose(fpointer);
                    if (logger) {
                        char message[FILEPATH_MAX_LEN] = "File \"";
                        strcat(message, buf);
                        strcat(message, "\" closed");
                        logcat(logger, message, INFO);
                    }
                } else if (!strcmp(ext, "h")) {
                    fpointer = fopen(buf, "w");
                    fclose(fpointer);
                    if (logger) {
                        char message[FILEPATH_MAX_LEN] = "File \"";
                        strcat(message, buf);
                        strcat(message, "\" cleared");
                        logcat(logger, message, INFO);
                    }
                }
            }
        }
    }
}

void apply_cesar(int shift, FILE *fpointer) {
    int ch;
    do {
        int tmp = shift;
        ch = fgetc(fpointer);
        if (ch != EOF) {
            if (ch + shift > 126)
                tmp = (ch + shift - 32) % 95 - 95;
            else if (ch + shift < 32)
                tmp = (ch + shift - 32) % 95 + 95;
            ch += tmp;
            fseek(fpointer, -1, SEEK_CUR);
            fputc(ch, fpointer);
        }
    } while (ch != EOF);
}