#include "data_stat.h"

#include <math.h>

double max(const double *data, int n) {
    double max = data[0];
    for (int col = 1; col < n; col++) {
        if (max < data[col]) max = data[col];
    }
    return max;
}

double min(const double *data, int n) {
    double min = data[0];
    for (int col = 1; col < n; col++) {
        if (min > data[col]) min = data[col];
    }
    return min;
}

double mean(const double *data, int n) {
    double mean = 0;
    for (int col = 0; col < n; col++) {
        mean += data[col];
    }
    mean = n != 0 ? mean / n : 0;
    return mean;
}

double variance(const double *data, int n) {
    double m = mean(data, n);
    double sum_sqr = 0;
    for (int col = 0; col < n; col++) {
        sum_sqr += pow(data[col] - m, 2);
    }
    return sum_sqr / n;
}