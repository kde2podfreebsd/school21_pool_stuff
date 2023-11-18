#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "decision.h"

int main() {
    int n, error = 0;

    if (scanf("%d", &n) && n >= 1) {
        double *data = malloc(n * sizeof(double));
        error = input(data, n);

        if (!error) {
            if (make_decision(data, n))
                printf("YES");
            else
                printf("NO");
        }

        free(data);
    } else
        error = 1;

    if (error) printf("ERROR");

    return 0;
}
