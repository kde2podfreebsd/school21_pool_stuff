#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define OK 0
#define ERR 1
#define FILENAME_LEN 100000
#define MAX_FILES 100000

int get_answer();
void encryptCesar(char *text, int key);
int isFileEmpty(const char* fileName);
int readFile(const char* fileName, char** fileBuffer);
int appendFile(const char* fileName, char* fileBuffer);
void readDirectory(char *path, const char *extension, char *files[MAX_FILES]);
int isExtension(const char *filename, const char *extension);

int main() {
    char filename[FILENAME_LEN];
    char* dirPath_C[MAX_FILES];
    char* dirPath_H[MAX_FILES];
    char directoryPath[FILENAME_LEN];

    const char *targetExtensionC = ".c";
    const char *targetExtensionH = ".h";

    int is_file_read = 0;
    int choice;
    char* buffer = NULL;

    for (int i = 0; i < MAX_FILES; ++i) {
        dirPath_C[i] = NULL;
        dirPath_H[i] = NULL;
    }

    do {
        choice = get_answer();
    
    if(choice == -1){
        break;
    }
    else if (choice == 1) {
        
            scanf("%s", filename);
            if (!readFile(filename, &buffer)) {
                is_file_read = 1;
                if(isFileEmpty(filename)){
                    printf("n/a\n");
                } else{
                    printf("%s\n", buffer);
                }
            } else {
                printf("n/a\n");
                is_file_read = 0;
            }
        } else if (choice == 2) {
            char data[FILENAME_LEN];

            scanf("%s", data);

            if (is_file_read) {
                if (appendFile(filename, data)) {
                    printf("n/a\n");
                } else {
                    if (!readFile(filename, &buffer)) {
                        printf("%s\n", buffer);
                    } else {
                        printf("n/a\n");
                    }
                }
            } else {
                printf("n/a\n");
            }
        }else if (choice == 3) {
            scanf("%s", directoryPath);
            readDirectory(directoryPath, targetExtensionC, dirPath_C);
            readDirectory(directoryPath, targetExtensionH, dirPath_H);

            for (int i = 0; i < MAX_FILES && dirPath_C[i] != NULL; ++i) {
                char *dir_path_copy = strdup(directoryPath);
                strcat(dir_path_copy, dirPath_C[i]);
                // FILE* file = fopen(, "a");
                printf("%s\n", dir_path_copy);
                free(dirPath_C[i]);
            }

            for (int i = 0; i < MAX_FILES && dirPath_H[i] != NULL; ++i) {
                char *dir_path_copy = strdup(directoryPath);
                strcat(dir_path_copy, dirPath_H[i]);
                FILE* file = fopen(dir_path_copy, "w");
                fclose(file);
                printf("%s\n", dir_path_copy);
                free(dirPath_H[i]);
            }
        } else {
            printf("n/a\n");
        }
    } while(choice != -1);
    return OK;
}


int get_answer() {
    int answer = 0;
    int result = 0;
    do {
        result = scanf("%d", &answer);
        if (result != 1) {
            printf("n/a\n");
            scanf("%*[^\n]"); 
        }
    } while (result != 1);

    return answer;
}

void encryptCesar(char *text, int key) {
    for (int i = 0; text[i] != '\0'; ++i) {
        if (text[i] >= 33 && text[i] <= 126) {
            text[i] = (text[i] - 33 + key) % 94 + 33;
        }
    }
}

int isFileEmpty(const char* fileName) {
    FILE* file = fopen(fileName, "r");

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fclose(file);

    return fileSize == 0;
}
 
int readFile(const char* fileName, char** fileBuffer) {
    FILE* file = fopen(fileName, "r");

    if (file == NULL) {
        return ERR;
    }

    int i = 0;

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    *fileBuffer = malloc(fileSize + 1);
    if (*fileBuffer == NULL) {
        fclose(file);
        return ERR;
    }

    while (i < fileSize && fscanf(file, "%c", &(*fileBuffer)[i]) != EOF) {
        i++;
    }

    (*fileBuffer)[i] = '\0';
    fclose(file);

    return OK;
}

int appendFile(const char* fileName, char* fileBuffer) {
    FILE* file = fopen(fileName, "a");

    if (file == NULL) {
        return ERR;
    }
    int i;
    for (i = 0; fileBuffer[i] != '\0'; i++) {
        fprintf(file, "%c", fileBuffer[i]);
    }

    fclose(file);

    return OK;
}

void readDirectory(char *path, const char *extension, char *files[MAX_FILES]) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    int i = 0;  // Индекс для записи в массив files

    while ((entry = readdir(dir)) != NULL && i < MAX_FILES - 1) {
        if (isExtension(entry->d_name, extension)) {
            // Выделяем память для имени файла и копируем его
            files[i] = malloc(strlen(entry->d_name) + 1);
            if (files[i] == NULL) {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            strcpy(files[i], entry->d_name);

            i++;  // Увеличиваем индекс для следующей записи
        }
    }

    files[i] = NULL;  // Устанавливаем конец массива
    closedir(dir);
}

int isExtension(const char *filename, const char *extension) {
    size_t filenameLength = strlen(filename);
    size_t extensionLength = strlen(extension);

    if (filenameLength < extensionLength) {
        return 0;  // Имя файла короче расширения, оно не может иметь такое расширение
    }

    return (strcmp(filename + filenameLength - extensionLength, extension) == 0);
}
