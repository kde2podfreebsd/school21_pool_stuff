#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#include "log_levels.h"

FILE *log_init(char *filename);
void logcat(FILE *log_file, char *message, Log_levels level);
void log_close(FILE *log_file);

#endif