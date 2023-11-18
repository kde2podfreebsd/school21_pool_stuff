#include <stdio.h>
#include <stdlib.h>

int input(int** matrix, int n, int m);
void output(int** matrix, int n, int m);

void sum(int** matrix1, int n1, int m1, int** matrix2, int** result);
void mul(int** matrix1, int m1, int** matrix2, int** result, int nr, int mr);
void transpose(int** matrix, int n, int m, int** result);

int main() {
    int action, error = 0;

    scanf("%d", &action);
    if (action < 1 || action > 3)
        error = 1;
    else {
        int n1, m1, n2, m2;

        scanf("%d %d", &n1, &m1);
        if (n1 < 1 || m1 < 1)
            error = 1;
        else {
            int** matrix1;
            int** matrix2;
            int** result;
            int nr, mr;

            matrix1 = malloc(n1 * m1 * sizeof(int) + n1 * sizeof(int*));
            int* ptrs1 = (int*)(matrix1 + n1);
            for (int i = 0; i < n1; i++) matrix1[i] = ptrs1 + m1 * i;
            error = input(matrix1, n1, m1);

            if (!error && action == 1) {
                scanf("%d %d", &n2, &m2);
                if (n2 >= 1 && m2 >= 1 && n1 == n2 && m1 == m2) {
                    matrix2 = malloc(n2 * m2 * sizeof(int) + n2 * sizeof(int*));
                    int* ptrs2 = (int*)(matrix2 + n2);
                    for (int i = 0; i < n2; i++) matrix2[i] = ptrs2 + m2 * i;
                    error = input(matrix2, n2, m2);

                    nr = n1;
                    mr = m1;
                    result = malloc(nr * mr * sizeof(int) + nr * sizeof(int*));
                    int* ptrsr = (int*)(result + nr);
                    for (int i = 0; i < nr; i++) result[i] = ptrsr + mr * i;
                    sum(matrix1, n1, m1, matrix2, result);
                    output(result, nr, mr);
                    free(result);
                    free(matrix2);
                } else
                    error = 1;
            } else if (!error && action == 2) {
                scanf("%d %d", &n2, &m2);
                if (n2 >= 1 && m2 >= 1 && m1 == n2) {
                    matrix2 = malloc(n2 * m2 * sizeof(int) + n2 * sizeof(int*));
                    int* ptrs2 = (int*)(matrix2 + n2);
                    for (int i = 0; i < n2; i++) matrix2[i] = ptrs2 + m2 * i;
                    error = input(matrix2, n2, m2);

                    nr = n1;
                    mr = m2;
                    result = malloc(nr * mr * sizeof(int) + nr * sizeof(int*));
                    int* ptrsr = (int*)(result + nr);
                    for (int i = 0; i < nr; i++) result[i] = ptrsr + mr * i;
                    mul(matrix1, m1, matrix2, result, nr, mr);
                    output(result, nr, mr);
                    free(result);
                    free(matrix2);
                } else
                    error = 1;
            } else if (!error && action == 3) {
                nr = m1;
                mr = n1;
                result = malloc(nr * mr * sizeof(int) + nr * sizeof(int*));
                int* ptrsr = (int*)(result + nr);
                for (int i = 0; i < nr; i++) result[i] = ptrsr + mr * i;
                transpose(matrix1, n1, m1, result);
                output(result, nr, mr);
                free(result);
            }
            free(matrix1);
        }
    }

    if (error) printf("n/a");

    return 0;
}

int input(int** matrix, int n, int m) {
    int error = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!scanf("%d", &matrix[i][j])) error = 1;
        }
    }

    return error;
}

void output(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", matrix[i][j]);
            if (j != cols - 1) printf(" ");
        }
        if (i != rows - 1) printf("\n");
    }
}

void sum(int** matrix1, int n1, int m1, int** matrix2, int** result) {
    for (int row = 0; row < n1; row++) {
        for (int col = 0; col < m1; col++) {
            result[row][col] = matrix1[row][col] + matrix2[row][col];
        }
    }
}

void mul(int** matrix1, int m1, int** matrix2, int** result, int nr, int mr) {
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < mr; j++) {
            result[i][j] = 0;
            for (int k = 0; k < m1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void transpose(int** matrix, int n, int m, int** result) {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            result[col][row] = matrix[row][col];
        }
    }
}