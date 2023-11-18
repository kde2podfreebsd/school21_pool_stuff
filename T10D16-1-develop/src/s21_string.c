#include "s21_string.h"

#include <stdio.h>

long unsigned int s21_strlen(const char *str) {
    long unsigned int length = 0;
    for (; *(str + length); length++)
        ;
    return length;
}

int s21_strcmp(const char *str1, const char *str2) {
    for (; *str1 && *str1 == *str2; str1++, str2++)
        ;
    return *str1 - *str2;
}

char *s21_strcpy(char *str1, const char *str2) {
    long unsigned int len2 = s21_strlen(str2);
    for (long unsigned int i = 0; i < s21_strlen(str2); i++) {
        str1[i] = str2[i];
    }
    str1[len2] = '\0';
    return str1;
}

char *s21_strcat(char *str1, const char *str2) {
    long unsigned int len1 = s21_strlen(str1);
    long unsigned int len2 = s21_strlen(str2);
    for (long unsigned int i = 0; i < len2; i++) {
        str1[len1 + i] = str2[i];
    }
    str1[len1 + len2] = '\0';
    return str1;
}

char *s21_strchr(const char *str, int ch) {
    char *pointer = NULL;
    for (long unsigned int i = 0; i < s21_strlen(str); i++) {
        if (str[i] == ch) {
            pointer = (char *)(str + i);
            break;
        }
    }
    return pointer;
}

char *s21_strstr(const char *str1, const char *str2) {
    char *pointer = NULL;
    for (long unsigned int i = 0; i < s21_strlen(str1) - s21_strlen(str2); i++) {
        if (str1[i] == str2[0]) {
            int flag = 1;
            for (long unsigned int j = i; j < s21_strlen(str2) + i; j++) {
                if (str1[j] != str2[j - i]) flag = 0;
            }
            if (flag) {
                pointer = (char *)(str1 + i);
                break;
            }
        }
    }
    return pointer;
}

char *s21_strtok(char *str, char *sep) {
    static char *backup_str;

    if (!str) str = backup_str;
    if (!str) return NULL;

    char *sep_pos = s21_strchr(str, *sep);
    if (sep_pos == NULL) {
        backup_str = NULL;
        return str;
    }

    char *result = str;
    if (*sep_pos == '\0')
        backup_str = str;
    else {
        backup_str = sep_pos + 1;
        *sep_pos = '\0';
    }

    return result;
}