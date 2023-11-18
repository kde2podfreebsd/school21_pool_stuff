#include "data_plot.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void make_plot(int **matrix) {
    for (int i = 0; i < ROWS_X; i++) {
        for (int j = 0; j < COLUMNS_Y; j++) {
            if (matrix[i][j] == 1) {
                printf("*");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}