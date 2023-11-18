#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

#define LEN_MAX 100

int main(int argc, char **argv) {
    int error = 0;

    if (argc == 2 && s21_strcmp(argv[1], "-w") == 0) {
        int len;
        if (!scanf("%d", &len)) error = 1;
        if (!error) {
            char str[LEN_MAX] = {'\0'};
            char buf[LEN_MAX] = {'\0'};
            char ch = getchar();
            int counter = 0;
            do {
                ch = getchar();
                if (ch != '\n') {
                    str[counter] = ch;
                    counter++;
                }
            } while (ch != '\n');

            char *word = s21_strtok(str, " ");
            int j = 0;
            while (word != NULL) {
                s21_strcpy(buf, word);
                for (int i = 0; i < (int)s21_strlen(buf);) {
                    if (j == len - 1 && i != (int)s21_strlen(buf) && (int)s21_strlen(buf) > len) {
                        printf("-\n");
                        j = 0;
                    } else if (j <= len - 1) {
                        printf("%c", buf[i]);
                        j++;
                        i++;
                    }
                }

                word = s21_strtok(NULL, " ");
                if (j != 0 && word != NULL &&
                    ((int)s21_strlen(word) + j < len - 1 || (int)s21_strlen(word) > len)) {
                    printf(" ");
                    j++;
                } else if (word != NULL) {
                    printf("\n");
                    j = 0;
                }
            }
        }
    } else
        error = 1;

    if (error) printf("n/a");

    return 0;
}
