#include <stdio.h>
#include <stdlib.h>
#include "s21_string.h"


// длинна строки
int s21_strlen(char* str){
    int count = 0;
    for(int i = 0; str[i] != '\0'; ++i){
        count++;
    }

    return count;
}

// лексикографический порядок (если str1 > str2 = +1 иначе  -1)
int s21_strcmp(char* str1, char* str2){
    int result = 0;

    int size1 = s21_strlen(str1);
    int size2 = s21_strlen(str2);

    if(size1 == size2){
        for(int i = 0; i < size1; ++i){
            if(str1[i] != str2[i]){
                if(str1[i] > str2[i]){
                    result = 1;
                } else {
                    result = -1;
                }
                break;
            }
            result = 0;
        }
    }

    if(size1 > size2) result = 1;
    if(size2 > size1) result = -1;

    return result;
}

// коиприование строки в строку 
char* s21_strcpy(char* str1, char* str2){
    int i;
    for(i = 0; str1[i] != '\0'; ++i){
        str2[i] = str1[i];
    }
    str2[i] = '\0';
    return str2;
}

// конкатенирование строк
char* s21_strcat(char* str1, char* str2) {
    str1 = realloc(str1, s21_strlen(str1) + s21_strlen(str2) + 1);
    int count = 0;
    for(int i = s21_strlen(str1), j = 0; i < s21_strlen(str1) + s21_strlen(str2) + 1; ++i, ++j){
        str1[i] = str2[j];
        count++;
    }

    return str1;
}

//вхождение символа в строку вовзаращаем указатель
const char* s21_strchr(const char* str, char c) {
    if (*str == '\0') {
        return NULL;
    }

    while (*str != '\0') {
        if (*str == c) {
            return str;
        }
        str++;
    }

    return NULL;
}

//
#ifndef S21_STRING_H
#define S21_STRING_H

int s21_strlen(char* str);
int s21_strcmp(char* str1, char* str2);
char* s21_strcpy(char* str1, char* str2);
char* s21_strcat(char* str1, char* str2);
char* s21_strchr(const char *str, char c);
// char* s21_strstr(char *str1, char *str2);

#endif




