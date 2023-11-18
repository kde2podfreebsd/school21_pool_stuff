#include <stdio.h>
#include <stdlib.h>

double **input(int *rows, int *cols, int *error);
void output(double **matrix, int n, int m);
double **allocate_matrix(int rows, int cols);

void getSubMatrix(double **matrix, int rows, int cols, double **subMatrix, int p, int q);
double det(double **matrix, int rows, int cols);

double **adjoint(double **matrix, int rows, int cols);
double **invert(double **matrix, int rows, int cols);

int main() {
    int n, m, error = 0;
    double **matrix = input(&n, &m, &error);

    if (!error) {
        double **result = invert(matrix, n, m);

        if (result != NULL) {
            output(result, n, m);
        } else
            error = 1;
        free(result);
    }

    if (error) printf("n/a");

    free(matrix);

    return 0;
}

double **input(int *rows, int *cols, int *error) {
    scanf("%d %d", rows, cols);

    double **matrix = allocate_matrix(*rows, *cols);

    if (*rows >= 1 && *cols >= 1 && *rows == *cols) {
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

double det(double **matrix, int rows, int cols) {
    double D = 0;

    if (rows == 1) return matrix[0][0];

    int sign = 1;

    for (int i = 0; i < rows; i++) {
        double **subMatrix = allocate_matrix(rows, cols);
        getSubMatrix(matrix, rows, cols, subMatrix, 0, i);
        D += sign * matrix[0][i] * det(subMatrix, rows - 1, cols - 1);
        sign = -sign;
        free(subMatrix);
    }

    return D;
}

double **invert(double **matrix, int rows, int cols) {
    double D = det(matrix, rows, cols);
    if (D == 0) return NULL;

    double **result = allocate_matrix(rows, cols);
    double **adj = adjoint(matrix, rows, cols);
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            result[row][col] = adj[row][col] / D;
        }
    }

    free(adj);

    return result;
}

double **adjoint(double **matrix, int rows, int cols) {
    double **adjoint = allocate_matrix(rows, cols);

    if (rows == 1) {
        adjoint[0][0] = 1;
        return adjoint;
    }

    double **tmp = allocate_matrix(rows, cols);

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            getSubMatrix(matrix, rows, cols, tmp, row, col);
            int sign = ((row + col) % 2 == 0) ? 1 : -1;
            adjoint[col][row] = sign * det(tmp, rows - 1, cols - 1);
        }
    }

    free(tmp);

    return adjoint;
}

void output(double **matrix, int n, int m) {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            printf("%.6lf", matrix[row][col]);
            if (col != m - 1) printf(" ");
        }
        if (row != n - 1) printf("\n");
    }
}
