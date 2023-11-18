#include "data_io.h"

#include <stdio.h>

int input(double *data, int n) {
    int error = 0;
    for (int col = 0; col < n; col++) {
        if (!scanf("%lf", &data[col])) error = 1;
    }
    return error;
}

void output(const double *data, int n) {
    for (int col = 0; col < n; col++) {
        printf("%.2lf", data[col]);
        if (col != n - 1) printf(" ");
    }
}