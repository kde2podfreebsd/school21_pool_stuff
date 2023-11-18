#include <stdio.h>
#include <stdlib.h>

#define STATIC_LEN 100

int input_2d_array_size(int* rows, int* cols);
int input_2d_array(int** array2d, int rows, int cols);
void print_1d_array(const int* array1d, int cols);
void print_2d_array(const int** array2d, int rows, int cols);
void free_2d_array(int n, int** array2d, int rows);

void find_rows_maxs(int** array2d, int rows, int cols, int* result);
void find_cols_mins(int** array2d, int rows, int cols, int* result);

int main() {
    int n, error = 0;
    int rows, cols;

    error = !scanf("%d", &n);
    if (n < 1 || n > 4) error = 1;

    if (!error) error = input_2d_array_size(&rows, &cols);
    if (!error) {
        int** matrix;
        const int matrix_static[rows][cols];
        int* pointers[rows];
        for (int i = 0; i < rows; i++) pointers[i] = (int*)matrix_static[i];
        matrix = pointers;

        if (n == 2) {
            int** single_array = malloc(rows * cols * sizeof(int) + rows * sizeof(int*));
            int* ptrs = (int*)(single_array + rows);
            for (int i = 0; i < rows; i++) single_array[i] = ptrs + cols * i;
            matrix = single_array;
        } else if (n == 3) {
            int** pointer_array = malloc(rows * sizeof(int*));
            for (int i = 0; i < rows; i++) pointer_array[i] = malloc(cols * sizeof(int));
            matrix = pointer_array;
        } else if (n == 4) {
            int** pointer_array = malloc(rows * sizeof(int*));
            int* values_array = malloc(rows * cols * sizeof(int));
            for (int i = 0; i < rows; i++) pointer_array[i] = values_array + cols * i;
            matrix = pointer_array;
        }

        error = input_2d_array(matrix, rows, cols);

        if (!error) {
            print_2d_array((const int**)matrix, rows, cols);

            int rows_maxs[rows];
            int cols_mins[cols];

            find_rows_maxs(matrix, rows, cols, rows_maxs);
            find_cols_mins(matrix, rows, cols, cols_mins);

            printf("\n");
            print_1d_array(rows_maxs, rows);
            printf("\n");
            print_1d_array(cols_mins, cols);

            if (n != 1) free_2d_array(n, matrix, rows);
        }
    } else
        printf("n/a");

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

void find_rows_maxs(int** array2d, int rows, int cols, int* result) {
    for (int row = 0; row < rows; row++) {
        int row_max = array2d[row][0];
        for (int col = 1; col < cols; col++) {
            if (row_max < array2d[row][col]) row_max = array2d[row][col];
        }
        result[row] = row_max;
    }
}

void find_cols_mins(int** array2d, int rows, int cols, int* result) {
    for (int col = 0; col < cols; col++) {
        int col_min = array2d[0][col];
        for (int row = 1; row < rows; row++) {
            if (col_min > array2d[row][col]) col_min = array2d[row][col];
        }
        result[col] = col_min;
    }
}

void print_1d_array(const int* array1d, int cols) {
    for (int col = 0; col < cols; col++) {
        printf("%d", array1d[col]);
        if (col != cols - 1) printf(" ");
    }
}