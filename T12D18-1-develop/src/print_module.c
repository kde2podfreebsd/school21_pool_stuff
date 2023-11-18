#include "print_module.h"

#include <stdio.h>
#include <time.h>

void print_log(char (*print_char)(char), char *message) {
    char time_str[10];
    time_t current_time = time(NULL);
    struct tm *time_info = localtime(&current_time);
    strftime(time_str, sizeof(time_str), " %H:%M:%S ", time_info);

    char *log = Log_prefix;

    for (; *log; log++) print_char(*log);
    for (int i = 0; i < 10; i++) print_char(time_str[i]);
    for (; *message; message++) print_char(*message);
}

char print_char(char ch) { return putchar(ch); }
