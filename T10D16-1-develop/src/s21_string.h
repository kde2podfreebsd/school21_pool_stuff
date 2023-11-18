#ifndef S21_STRING_H
#define S21_STRING_H

long unsigned int s21_strlen(const char *str);
int s21_strcmp(const char *str1, const char *str2);
char *s21_strcpy(char *str1, const char *str2);
char *s21_strcat(char *str1, const char *str2);
char *s21_strchr(const char *str, int ch);
char *s21_strstr(const char *str1, const char *str2);
char *s21_strtok(char *str1, char *str2);

void s21_strlen_test();
void s21_strcmp_test();
void s21_strcpy_test();
void s21_strcat_test();
void s21_strchr_test();
void s21_strstr_test();
void s21_strtok_test();

#endif