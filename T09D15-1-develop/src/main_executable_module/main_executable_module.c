#include <stdio.h>
#include <stdlib.h>

#ifdef TYPE
#include "../data_libs/data_io_macro.h"
DEF_INPUT(TYPE);
DEF_OUTPUT(TYPE);
#else
#include "../data_libs/data_io.h"
#define TYPE double
#endif

#include "../data_libs/data_stat.h"
#include "../data_module/data_process.h"
#include "../yet_another_decision_module/decision.h"

int main() {
    int n, error = 0;

    if (scanf("%d", &n) && n >= 1) {
        TYPE *data = malloc(n * sizeof(TYPE));
        printf("LOAD DATA...\n");
        error = input(data, n);

        if (!error) {
            printf("RAW DATA:\n\t");
            output(data, n);

            printf("\nNORMALIZED DATA:\n\t");
            normalization(data, n);
            output(data, n);

            printf("\nSORTED NORMALIZED DATA:\n\t");
            sort(data, n, 0);
            output(data, n);

            printf("\nFINAL DECISION:\n\t");
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
