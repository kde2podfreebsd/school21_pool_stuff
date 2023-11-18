#include "data_process.h"

#include <math.h>

#include "../data_libs/data_stat.h"

int normalization(double *data, int n) {
    int result = 1;
    double max_value = max(data, n);
    double min_value = min(data, n);
    double size = max_value - min_value;

    if (fabs(size) > EPS) {
        for (int i = 0; i < n; i++) {
            data[i] = (data[i] - min_value) / size;
        }
    } else {
        result = 0;
    }

    return result;
}

void swap(double *a, double *b) {
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort(double *data, int n, int dec) {
    for (int col = 0; col < n - 1; col++) {
        for (int i = col + 1; i < n; i++) {
            if ((!dec && data[col] > data[i]) || (dec && data[col] < data[i])) swap(&data[col], &data[i]);
        }
    }
}