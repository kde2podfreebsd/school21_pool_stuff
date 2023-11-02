#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERR 1
#define NMAX 100

int dynamicAllocate1(int ***a, int n, int m);
int dynamicAllocate2(int ***a, int n, int m);
int dynamicAllocate3(int ***a, int n, int m);

void freeDynamic1(int ***a, int n);
void freeDynamic2(int ***a);
void freeDynamic3(int ***a);

int input(int **a, int n, int m);
void output(int **a, int n, int m);

int inputStatic(int a[][NMAX], int n, int m);
void outputStatic(int a[][NMAX], int n, int m);

void output_array(int* a, int m);

void findMaxInRow(int **a, int n, int m, int *b);
void findMinInColumn(int **a, int n, int m, int *b);

int main() {
    int flag = OK;
    int **array;
    int *max_row;
    int *min_column;
    int n = 0;
    int m = 0;
    int mode = 0;

    if (scanf("%d", &mode) == 1 && mode > 0 && mode <= 4) {
        if (scanf("%d %d", &n, &m) == 2 && n > 0 && m > 0) {
            switch (mode) {
                case 1:
                    if (n > 100 || m > 100) {
                        flag = ERR;
                        printf("n/a");
                        break;
                    } else {
                        int b[NMAX][NMAX];
                        if(inputStatic(b, n, m)){
                            printf("n/a");
                            flag = ERR;
                            break;
                        }
                        outputStatic(b, n, m);
                        break;
                    }
                case 2:
                    if (dynamicAllocate1(&array, n, m)) {
                        printf("n/a");
                        flag = ERR;
                        freeDynamic1(&array, n);
                        break;
                    }
                    if(input(array, n, m)){
                        printf("n/a");
                        flag = ERR;
                        freeDynamic1(&array, n);
                        break;
                    }
                    output(array, n, m);
                    max_row = calloc(m, sizeof(int));
                    if(max_row == NULL){
                        printf("n/a");
                        flag = ERR;
                        break;
                    }
                    min_column = calloc(n, sizeof(int));
                    if(min_column == NULL){
                        printf("n/a");
                        flag = ERR;
                        break;
                    }
                    findMaxInRow(array, n, m, max_row);
                    findMinInColumn(array, n, m, min_column);
                    printf("\n");
                    output_array(max_row, m);
                    printf("\n");
                    output_array(min_column, m);
                    freeDynamic1(&array, n);
                    free(max_row);
                    free(min_column);
                    break;
                case 3:
                    if (dynamicAllocate2(&array, n, m)) {
                        printf("n/a");
                        flag = ERR;
                        freeDynamic2(&array);
                        break;
                    }
                    if(input(array, n, m)){
                        printf("n/a");
                        flag = ERR;
                        freeDynamic2(&array);
                        break;
                    }
                    output(array, n, m);
                    max_row = calloc(m, sizeof(int));
                    if(max_row == NULL){
                        printf("n/a");
                        flag = ERR;
                        break;
                    }
                    min_column = calloc(n, sizeof(int));
                    if(min_column == NULL){
                        printf("n/a");
                        flag = ERR;
                        break;
                    }
                    findMaxInRow(array, n, m, max_row);
                    findMinInColumn(array, n, m, min_column);
                    printf("\n");
                    output_array(max_row, m);
                    printf("\n");
                    output_array(min_column, m);
                    freeDynamic2(&array);
                    free(max_row);
                    free(min_column);
                    break;
                case 4:
                    if (dynamicAllocate3(&array, n, m)) {
                        printf("n/a");
                        flag = ERR;
                        freeDynamic3(&array);
                        break;
                    }
                    if(input(array, n, m)){
                        printf("n/a");
                        flag = ERR;
                        freeDynamic3(&array);
                        break;
                    }
                    output(array, n, m);
                    max_row = calloc(m, sizeof(int));
                    if(max_row == NULL){
                        printf("n/a");
                        flag = ERR;
                        break;
                    }
                    min_column = calloc(n, sizeof(int));
                    if(min_column == NULL){
                        printf("n/a");
                        flag = ERR;
                        break;
                    }
                    findMaxInRow(array, n, m, max_row);
                    findMinInColumn(array, n, m, min_column);
                    printf("\n");
                    output_array(max_row, m);
                    printf("\n");
                    output_array(min_column, m);
                    freeDynamic3(&array);
                    free(max_row);
                    free(min_column);
                    break;
            }
        } else {
            printf("n/a");
            flag = ERR;
        }
    } else {
        flag = ERR;
    }

    return flag;
}

int dynamicAllocate1(int ***a, int n, int m) {
    int flag = OK;

    *a = calloc(n, sizeof(int *));
    if (*a == NULL) {
        flag = ERR;
    } else {
        for (int i = 0; i < n; i++) {
            (*a)[i] = calloc(m, sizeof(int));
            if ((*a)[i] == NULL) {
                flag = ERR;
            }
        }
    }

    return flag;
}

void freeDynamic1(int ***a, int n) {
    for (int i = 0; i < n; ++i) {
        free((*a)[i]);
    }
    free(*a);
}

int dynamicAllocate2(int ***a, int n, int m) {
    int flag = OK;
    *a = malloc(n * sizeof(int) + m * n * sizeof(int *));
    if (*a == NULL) {
        flag = ERR;
    } else {
        for (int i = 0; i < n; ++i) {
            (*a)[i] = (int*)((*a) + n  + m * i);
        }
    }

    return flag;
}

void freeDynamic2(int ***a) { free(*a); }

int dynamicAllocate3(int ***a, int n, int m) {
    int flag = OK;
    *a = calloc(n, sizeof(int *));
    int *b = calloc(m, sizeof(int));

    if (a == NULL || b == NULL) {
        flag = ERR;
    } else {
        for (int i = 0; i < n; ++i) {
            (*a)[i] = &(b[m * i]);
        }
    }

    return flag;
}

void freeDynamic3(int ***a) {
    free((*a)[0]);
    free(*a);
}

int input(int **a, int n, int m) {
    int flag = OK;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if(scanf("%d", &a[i][j]) != 1){
                flag = ERR;
            }
        }
    }

    return flag;
}

void output(int **a, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d", a[i][j]);
            if (j < m - 1) {
                printf(" ");
            }
        }
        if (i < n - 1) {
            printf("\n");
        }
    }
}

int inputStatic(int a[][NMAX], int n, int m) {
    int flag = OK;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if(scanf("%d", &a[i][j]) != 1){
                flag = ERR;
            }
        }
    }

    return flag;
}

void outputStatic(int a[][NMAX], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d", a[i][j]);
            if (j < m - 1) {
                printf(" ");
            }
        }
        if (i < n - 1) {
            printf("\n");
        }
    }
}

void findMaxInRow(int **a, int n, int m, int *b){
    int max;

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if(j == 0){
                max = a[i][j];
            }

            if(a[i][j] > max){
                max = a[i][j];
            }
        }
        b[i] = max;
    }
}

void findMinInColumn(int **a, int n, int m, int *b) {
    for (int j = 0; j < m; ++j) {
        int min = a[0][j];

        for (int i = 1; i < n; ++i) {
            if (a[i][j] < min) {
                min = a[i][j];
            }
        }
        b[j] = min;
    }
}

void output_array(int* a, int m){
    for(int i = 0; i < m; ++i){
        printf("%d", a[i]);

        if(i < m -1){
            printf(" ");
        }
    }
}

