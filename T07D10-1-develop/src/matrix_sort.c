#include <stdio.h>
#include <stdlib.h>

#define STATIC_LEN 100

int input_2d_array_size(int* rows, int* cols);
int input_2d_array(int** array2d, int rows, int cols);
void print_1d_array(const int* array1d, int cols);
void print_2d_array(const int** array2d, int rows, int cols);
void free_2d_array(int n, int** array2d, int rows);

void matrix_sort(int** array2d, int rows, int cols);
int row_sum(const int* row, int cols);
void swap_row(int* row1, int* row2, int cols);

int main() {
    int n, error = 0;
    int rows, cols;

    if (!scanf("%d", &n) || n < 1 || n > 3)
        error = 1;
    else {
        error = input_2d_array_size(&rows, &cols);
        if (!error) {
            int** matrix;

            if (n == 1) {
                int** single_array = malloc(rows * cols * sizeof(int) + rows * sizeof(int*));
                int* ptrs = (int*)(single_array + rows);
                for (int i = 0; i < rows; i++) single_array[i] = ptrs + cols * i;
                matrix = single_array;
            } else if (n == 2) {
                int** pointer_array = malloc(rows * sizeof(int*));
                for (int i = 0; i < rows; i++) pointer_array[i] = malloc(cols * sizeof(int));
                matrix = pointer_array;
            } else {
                int** pointer_array = malloc(rows * sizeof(int*));
                int* values_array = malloc(rows * cols * sizeof(int));
                for (int i = 0; i < rows; i++) pointer_array[i] = values_array + cols * i;
                matrix = pointer_array;
            }

            error = input_2d_array(matrix, rows, cols);

            if (!error) {
                matrix_sort(matrix, rows, cols);

                print_2d_array((const int**)matrix, rows, cols);

                free_2d_array(n, matrix, rows);
            }
        }
    }

    if (error) printf("n/a");

    return 0;
}

int input_2d_array_size(int* rows, int* cols) {
    int error = 0;
    if (scanf("%d %d", rows, cols) < 2) error = 1;
    if (*rows > STATIC_LEN || *cols > STATIC_LEN) error = 1;
    return error;
}

int input_2d_array(int** array2d, int rows, int cols) {
    int error = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!scanf("%d", &array2d[i][j])) error = 1;
        }
    }
    return error;
}

void print_2d_array(const int** array2d, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", array2d[i][j]);
            if (j != cols - 1) printf(" ");
        }
        if (i != rows - 1) printf("\n");
    }
}

void free_2d_array(int n, int** array2d, int rows) {
    if (n == 3)
        for (int i = 0; i < rows; i++) free(array2d[i]);
    if (n == 4) free(array2d[0]);
    free(array2d);
}

void print_1d_array(const int* array1d, int cols) {
    for (int col = 0; col < cols; col++) {
        printf("%d", array1d[col]);
        if (col != cols - 1) printf(" ");
    }
}

void matrix_sort(int** array2d, int rows, int cols) {
    for (int i = 0; i < rows - 1; i++) {
        int row_min_sum = row_sum((const int*)array2d[i], cols);
        for (int j = i + 1; j < rows; j++) {
            if (row_min_sum > row_sum(array2d[j], cols)) swap_row(array2d[i], array2d[j], cols);
        }
    }
}

int row_sum(const int* row, int cols) {
    int sum = 0;
    for (int i = 0; i < cols; i++) sum += row[i];
    return sum;
}

void swap_row(int* row1, int* row2, int cols) {
    for (int i = 0; i < cols; i++) {
        int tmp = row1[i];
        row1[i] = row2[i];
        row2[i] = tmp;
    }
}