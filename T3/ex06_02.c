#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERR 0

int input(int ***array, int n, int m);
void output(int **array, int n, int m);
int findMin(int **array, int n, int m);
int findMax(int **array, int n, int m);
void swapRows(int **array, int row1, int row2);

int dynamicAllocate2(int ***a, int n, int m) {
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

void freeDynamic2(int ***a, int n) {
    for (int i = 0; i < n; ++i) {
        free((*a)[i]);
    }
    free(*a);
}

int main() {
    int n, m;
    int **matrix;
    int **output_matrix;

    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m <= 0) {
        printf("n/a");
        return 1;
    }

    if (dynamicAllocate2(&matrix, n, m) != OK) {
        printf("Memory allocation failed\n");
        return 1;
    }

    if (input(&matrix, n, m) != OK) {
        printf("Input failed\n");
        freeDynamic2(&matrix, n);
        return 1;
    }

    if (dynamicAllocate2(&output_matrix, n, m) != OK) {
        printf("Memory allocation failed\n");
        freeDynamic2(&matrix, n);
        return 1;
    }

    int minRow = findMin(matrix, n, m);
    int maxRow = findMax(matrix, n, m);

    swapRows(matrix, minRow, maxRow);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            output_matrix[i][j] = matrix[i][j];
        }
    }

    output(output_matrix, n, m);

    freeDynamic2(&matrix, n);
    freeDynamic2(&output_matrix, n);

    return 0;
}

int input(int ***array, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (scanf("%d", &(*array)[i][j]) != 1) {
                return ERR;
            }
        }
    }
    return OK;
}

void output(int **array, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d", array[i][j]);
            if (j < m - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int findMin(int **array, int n, int m) {
    int min = array[0][0];
    int minRow = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (array[i][j] < min) {
                min = array[i][j];
                minRow = i;
            }
        }
    }

    return minRow;
}

int findMax(int **array, int n, int m) {
    int max = array[0][0];
    int maxRow = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (array[i][j] > max) {
                max = array[i][j];
                maxRow = i;
            }
        }
    }

    return maxRow;
}

void swapRows(int **array,int row1, int row2) {
    int *tempRow = array[row1];
    array[row1] = array[row2];
    array[row2] = tempRow;
}