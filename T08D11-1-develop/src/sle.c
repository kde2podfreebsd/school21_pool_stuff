#include <stdio.h>
#include <stdlib.h>

double **input(int *rows, int *cols, int *error);
void output(double *roots, int cols);
double **allocate_matrix(int rows, int cols);

void sleCramer(double **matrix, int rows, int cols, double *roots, int *error);
double getDeterminant(double **matrix, int rows, int cols);
void getSubMatrix(double **matrix, int rows, int cols, double **subMatrix, int p, int q);

int main() {
    int n, m, error = 0;
    double **matrix = input(&n, &m, &error);

    if (!error) {
        double **roots = allocate_matrix(1, m - 1);
        sleCramer(matrix, n, m, roots[0], &error);
        output(roots[0], m - 1);
        free(roots);
    }

    if (error) printf("n/a");

    free(matrix);
    return 0;
}

double **input(int *rows, int *cols, int *error) {
    scanf("%d %d", rows, cols);

    double **matrix = allocate_matrix(*rows, *cols);

    if (*rows >= 1 && *cols >= 1 && *rows == *cols - 1) {
        for (int row = 0; row < *rows; row++)
            for (int col = 0; col < *cols; col++)
                if (!scanf("%lf", &matrix[row][col])) {
                    *error = 1;
                    break;
                }
    } else
        *error = 1;

    return matrix;
}

double **allocate_matrix(int rows, int cols) {
    double **matrix = malloc(rows * sizeof(double *) + rows * cols * sizeof(double));
    double *pointer = (double *)(matrix + rows);
    for (int i = 0; i < rows; i++) {
        matrix[i] = pointer + cols * i;
    }
    return matrix;
}

void output(double *roots, int cols) {
    for (int col = 0; col < cols; col++) {
        printf("%.6lf", roots[col]);
        if (col != cols - 1) printf(" ");
    }
}

double getDeterminant(double **matrix, int rows, int cols) {
    double D = 0;
    if (rows == 1) return matrix[0][0];

    int sign = 1;

    for (int i = 0; i < rows; i++) {
        double **subMatrix = allocate_matrix(rows, cols);
        getSubMatrix(matrix, rows, cols, subMatrix, 0, i);
        D += sign * matrix[0][i] * getDeterminant(subMatrix, rows - 1, cols - 1);
        sign = -sign;
        free(subMatrix);
    }

    return D;
}

void getSubMatrix(double **matrix, int rows, int cols, double **subMatrix, int p, int q) {
    int i = 0, j = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (row != p && col != q) {
                subMatrix[i][j++] = matrix[row][col];
                if (j == cols - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

void sleCramer(double **matrix, int rows, int cols, double *roots, int *error) {
    double D = getDeterminant(matrix, rows, cols);

    if (D == 0)
        *error = 1;
    else {
        double **tmp = allocate_matrix(rows, cols - 1);
        for (int root_i = 0; root_i < cols - 1; root_i++) {
            for (int row = 0; row < rows; row++) {
                for (int col = 0; col < cols - 1; col++) {
                    if (col == root_i)
                        tmp[row][col] = matrix[row][cols - 1];
                    else
                        tmp[row][col] = matrix[row][col];
                }
            }
            roots[root_i] = getDeterminant(tmp, rows, cols - 1) / D;
        }
        free(tmp);
    }
}