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

int main() {
    int flag = OK;
    int **array;
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
                        break;
                    }
                    if(input(array, n, m)){
                        printf("n/a");
                        flag = ERR;
                        break;
                    }
                    output(array, n, m);
                    freeDynamic1(&array, n);
                    break;
                case 3:
                    if (dynamicAllocate2(&array, n, m)) {
                        printf("n/a");
                        flag = ERR;
                        break;
                    }
                    if(input(array, n, m)){
                        printf("n/a");
                        flag = ERR;
                        break;
                    }
                    output(array, n, m);
                    freeDynamic2(&array);
                    break;
                case 4:
                    if (dynamicAllocate3(&array, n, m)) {
                        printf("n/a");
                        flag = ERR;
                        break;
                    }
                    if(input(array, n, m)){
                        printf("n/a");
                        flag = ERR;
                        break;
                    }
                    output(array, n, m);
                    freeDynamic3(&array);
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
    int *shift = ((int *)a + n);
    if (*a == NULL) {
        flag = ERR;
    } else {
        for (int i = 0; i < n; ++i) {
            (*a)[i] = shift + m * i;
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
