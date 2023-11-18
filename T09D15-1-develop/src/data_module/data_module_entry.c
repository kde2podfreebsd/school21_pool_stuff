#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "../data_libs/data_stat.h"
#include "data_process.h"

int main() {
    int n, error = 0;

    if (scanf("%d", &n) && n >= 1) {
        double *data = malloc(n * sizeof(double));
        error = input(data, n);

        if (!error && normalization(data, n))
            output(data, n);
        else
            error = 1;

        free(data);
    } else
        error = 1;

    if (error) printf("ERROR");

    return 0;
}
