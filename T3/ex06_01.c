#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERR 0

int input(int **array, int size);
void output(int **array, int size);
void matrixMul(int** matrix1, int** matrix2, int** output, int size);

int dynamicAllocate1(int ***a, int n, int m) {
    int flag = OK;

    *a = (int **)calloc(n, sizeof(int *));
    if (*a == NULL) {
        flag = ERR;
    } else {
        for (int i = 0; i < n; i++) {
            (*a)[i] = (int *)calloc(m, sizeof(int));
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

int main() {
    int size;
    int **matrix1;
    int **matrix2;
    int **output_matrix;

    if (scanf("%d", &size) != 1 || size <= 0) {
        printf("n/a");
        return 1;
    }

    if (dynamicAllocate1(&matrix1, size, size) != OK || dynamicAllocate1(&matrix2, size, size) != OK || dynamicAllocate1(&output_matrix, size, size) != OK) {
        printf("Memory allocation failed\n");
        freeDynamic1(&matrix1, size);
        freeDynamic1(&matrix2, size);
        freeDynamic1(&output_matrix, size);
        return 1;
    }

    input(matrix1, size);
    input(matrix2, size);

    matrixMul(matrix1, matrix2, output_matrix, size);

    output(output_matrix, size);

    freeDynamic1(&matrix1, size);
    freeDynamic1(&matrix2, size);
    freeDynamic1(&output_matrix, size);

    return 0;
}

int input(int **array, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (scanf("%d", &array[i][j]) != 1) {
                return ERR;
            }
        }
    }
    return OK;
}

void output(int **array, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%d", array[i][j]);
            if (j < size - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void matrixMul(int** matrix1, int** matrix2, int** output, int size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            for(int k = 0; k < size; ++k){
                output[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}