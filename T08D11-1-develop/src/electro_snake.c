#include <stdio.h>
#include <stdlib.h>
/*
    1 6 7
    2 5 8
    3 4 9
*/
void sort_vertical(int **matrix, int rows, int cols, int **result);

/*
    1 2 3
    6 5 4
    7 8 9
*/
void sort_horizontal(int **matrix, int n, int m, int **result);

int **input(int *rows, int *cols, int *error);
void output(int **matrix, int n, int m);
int **allocate_matrix(int rows, int cols);

int main() {
    int n, m, error = 0;
    int **matrix = input(&n, &m, &error);

    if (!error) {
        int **result = allocate_matrix(n, m);

        sort_vertical(matrix, n, m, result);
        output(result, n, m);

        printf("\n\n");

        sort_horizontal(matrix, n, m, result);
        output(result, n, m);

        free(matrix);
        free(result);
    }

    if (error) printf("n/a");

    return 0;
}

int **input(int *rows, int *cols, int *error) {
    scanf("%d %d", rows, cols);

    int **matrix = allocate_matrix(*rows, *cols);

    if (*rows >= 1 && *cols >= 1) {
        for (int row = 0; row < *rows; row++) {
            for (int col = 0; col < *cols; col++) {
                if (!scanf("%d", &matrix[row][col])) {
                    *error = 1;
                    break;
                }
            }
        }
    } else
        *error = 1;

    return matrix;
}

void output(int **matrix, int n, int m) {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            printf("%d", matrix[row][col]);
            if (col != m - 1) printf(" ");
        }
        if (row != n - 1) printf("\n");
    }
}

int **allocate_matrix(int rows, int cols) {
    int **matrix = malloc(rows * cols * sizeof(int) + rows * sizeof(int *));
    int *pointer = (int *)(matrix + rows);
    for (int i = 0; i < rows; i++) {
        matrix[i] = pointer + cols * i;
    }
    return matrix;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort_vertical(int **matrix, int rows, int cols, int **result) {
    int i = 0, j = 0, dir = 1;
    for (int cell = 0; cell < rows * cols - 1; cell++) {
        for (int cell_forward = cell + 1; cell_forward < rows * cols; cell_forward++) {
            if (matrix[cell / cols][cell % cols] > matrix[cell_forward / cols][cell_forward % cols]) {
                swap(&matrix[cell / cols][cell % cols], &matrix[cell_forward / cols][cell_forward % cols]);
            }
        }

        result[i][j] = matrix[cell / cols][cell % cols];
        i += dir;
        if (i == -1 || i == rows) {
            j++;
            dir *= -1;
            i += dir;
        }
    }
    result[i][j] = matrix[rows - 1][cols - 1];
}

void sort_horizontal(int **matrix, int rows, int cols, int **result) {
    int i = 0, j = 0, dir = 1;
    for (int cell = 0; cell < rows * cols - 1; cell++) {
        for (int cell_forward = cell + 1; cell_forward < rows * cols; cell_forward++) {
            if (matrix[cell / cols][cell % cols] > matrix[cell_forward / cols][cell_forward % cols]) {
                swap(&matrix[cell / cols][cell % cols], &matrix[cell_forward / cols][cell_forward % cols]);
            }
        }

        result[i][j] = matrix[cell / cols][cell % cols];
        j += dir;
        if (j == -1 || j == cols) {
            i++;
            dir *= -1;
            j += dir;
        }
    }
    result[i][j] = matrix[rows - 1][cols - 1];
}