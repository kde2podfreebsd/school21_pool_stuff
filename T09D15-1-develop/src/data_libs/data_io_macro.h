#ifndef DATA_IO_MACRO_H
#define DATA_IO_MACRO_H

#define DEF_INPUT(type)                               \
    int input(type *data, int n) {                    \
        int error = 0;                                \
        for (int col = 0; col < n; col++) {           \
            if (!scanf("%lf", &data[col])) error = 1; \
        }                                             \
        return error;                                 \
    }
#define DEF_OUTPUT(type)                    \
    void output(const type *data, int n) {  \
        for (int col = 0; col < n; col++) { \
            printf("%.2lf", data[col]);     \
            if (col != n - 1) printf(" ");  \
        }                                   \
    }

#endif