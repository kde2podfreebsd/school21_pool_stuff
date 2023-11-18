#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
#ifdef STRLEN
    s21_strlen_test();
#endif

#ifdef STRCMP
    s21_strcmp_test();
#endif

#ifdef STRCPY
    s21_strcpy_test();
#endif

#ifdef STRCAT
    s21_strcat_test();
#endif

#ifdef STRCHR
    s21_strchr_test();
#endif

#ifdef STRSTR
    s21_strstr_test();
#endif

#ifdef STRTOK
    s21_strtok_test();
#endif

    return 0;
}

#define STRLEN_N 3
#define STRCMP_N 3
#define STRCPY_N 3
#define STRCAT_N 3
#define STRCHR_N 3
#define STRSTR_N 3
#define STRTOK_N 3

void s21_strlen_test() {
    const char *tests[STRLEN_N] = {"string", "1", "abc"};
    const long unsigned int results[STRLEN_N] = {6, 1, 2};

    for (int i = 0; i < STRLEN_N; i++) {
        printf("%s\n", tests[i]);
        printf("%lu\n", results[i]);
        if (s21_strlen(tests[i]) == results[i])
            printf("SUCCESS");
        else
            printf("FAIL");
        if (i != STRLEN_N - 1) printf("\n");
    }
}

void s21_strcmp_test() {
    const char *tests1[STRCMP_N] = {"test", "1234", "abc"};
    const char *tests2[STRCMP_N] = {"test", "1", "abc"};
    const int results[STRLEN_N] = {0, 50, 1};

    for (int i = 0; i < STRCMP_N; i++) {
        printf("%s %s\n", tests1[i], tests2[i]);
        printf("%d\n", results[i]);
        if (s21_strcmp(tests1[i], tests2[i]) == results[i])
            printf("SUCCESS");
        else
            printf("FAIL");
        if (i != STRCMP_N - 1) printf("\n");
    }
}

void s21_strcpy_test() {
    const char *tests[STRCPY_N] = {"test", "abc", "123"};
    const char *results[STRCPY_N] = {tests[0], tests[1], "12"};

    for (int i = 0; i < STRCPY_N; i++) {
        char *s = calloc(s21_strlen(tests[i]), sizeof(char));
        printf("%p %s\n", &s, tests[i]);
        printf("%s\n", results[i]);
        s21_strcpy(s, tests[i]);
        if (!s21_strcmp(s21_strcpy(s, tests[i]), results[i]))
            printf("SUCCESS");
        else
            printf("FAIL");
        if (i != STRCPY_N - 1) printf("\n");
        free(s);
    }
}

void s21_strcat_test() {
    char *tests1[STRCAT_N] = {"test", "abc", "123"};
    const char *tests2[STRCAT_N] = {"test", "a", "123"};
    const char *results[STRCAT_N] = {"testtest", "abca", "123"};

    for (int i = 0; i < STRCAT_N; i++) {
        char *s = calloc(s21_strlen(tests1[i]) + s21_strlen(tests2[i]), sizeof(char));
        printf("%s %s\n", tests1[i], tests2[i]);
        printf("%s\n", results[i]);
        s21_strcpy(s, tests1[i]);
        s21_strcat(s, tests2[i]);
        if (!s21_strcmp(s, results[i]))
            printf("SUCCESS");
        else
            printf("FAIL");
        if (i != STRCAT_N - 1) printf("\n");
        free(s);
    }
}

void s21_strchr_test() {
    const char *tests[STRCHR_N] = {"test", "abtcfg", "1t23"};
    const char ch = 't';
    const char *results[STRCHR_N] = {"test", "tcfg", "23"};

    for (int i = 0; i < STRCHR_N; i++) {
        printf("%s %c\n", tests[i], ch);
        printf("%s\n", results[i]);
        char *result = s21_strchr(tests[i], ch);
        if (!s21_strcmp(results[i], result))
            printf("SUCCESS");
        else
            printf("FAIL");
        if (i != STRCAT_N - 1) printf("\n");
    }
}

void s21_strstr_test() {
    const char *tests1[STRSTR_N] = {"test", "abtcfg", "1t23"};
    const char *tests2[STRSTR_N] = {"es", "btc", "t2"};
    const char *results[STRSTR_N] = {"est", "btcfg", "23"};

    for (int i = 0; i < STRSTR_N; i++) {
        printf("%s %s\n", tests1[i], tests2[i]);
        printf("%s\n", results[i]);
        char *result = s21_strstr(tests1[i], tests2[i]);
        if (!s21_strcmp(results[i], result))
            printf("SUCCESS");
        else
            printf("FAIL");
        if (i != STRSTR_N - 1) printf("\n");
    }
}

void s21_strtok_test() {
    char test1_1[] = "test1/test2/test3/test4";
    char test1_2[] = "123_456";
    char test1_3[] = "1t23";
    char *tests2[STRTOK_N] = {"/", "_", "t"};
    const char *results[STRTOK_N] = {"test1", "123", "t233"};
    char *result;

    printf("%s %s\n", test1_1, tests2[0]);
    printf("%s\n", results[0]);
    result = s21_strtok(test1_1, tests2[0]);
    if (!s21_strcmp(results[0], result))
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");

    printf("%s %s\n", test1_2, tests2[1]);
    printf("%s\n", results[1]);
    result = s21_strtok(test1_2, tests2[1]);
    if (!s21_strcmp(results[1], result))
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");

    printf("%s %s\n", test1_3, tests2[2]);
    printf("%s\n", results[2]);
    result = s21_strtok(test1_3, tests2[2]);
    if (!s21_strcmp(results[2], result))
        printf("SUCCESS");
    else
        printf("FAIL");
    printf("\n");
}