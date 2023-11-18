#include "logger.h"

#include <stdio.h>
#include <time.h>

#include "log_levels.h"

FILE *log_init(char *filename) {
    FILE *file_pointer = fopen(filename, "a");
    return file_pointer;
}

void logcat(FILE *log_file, char *message, Log_levels level) {
    char time_str[10];
    time_t current_time = time(NULL);
    struct tm *time_info = localtime(&current_time);
    strftime(time_str, sizeof(time_str), "%H:%M:%S", time_info);

    char *level_str = "";
    if (level == DEBUG)
        level_str = "DEBUG";
    else if (level == INFO)
        level_str = "INFO";
    else if (level == WARNING)
        level_str = "WARNING";
    else if (level == ERROR)
        level_str = "ERROR";

    fprintf(log_file, "[%s] %s %s\n", level_str, time_str, message);
}

void log_close(FILE *log_file) { fclose(log_file); }