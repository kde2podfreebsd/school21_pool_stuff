#include <stdio.h>
#include <stdlib.h>

int input_length(int *n);
int input_array(int *a, int n);
void sort(int *a, int n);
void output_array(int *a, int n);

int main() {
    int n;
    int *data;
    int error = 0;

    error = input_length(&n);

    if (!error) {
        data = (int *)calloc(n, sizeof(int));
        if (data == NULL) {
            printf("n/a");
            error = 1;
        } else {
            error = input_array(data, n);
        }
    }

    if (!error) {
        sort(data, n);
        output_array(data, n);
        free(data);
    } else {
        printf("n/a");
    }

    return 0;
}

int input_length(int *n) {
    char ch;
    int error = 0;

    scanf("%d%c", n, &ch);
    if (ch != '\n' || *n <= 0) {
        error = 1;
    }

    return error;
}

int input_array(int *a, int n) {
    char ch;
    int error = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d%c", &a[i], &ch);
        if ((i < n - 1 && ch != ' ' && ch != '\n') || (i == n - 1 && ch != '\n')) {
            error = 1;
            break;
        }
    }

    return error;
}

void sort(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[i]) {
                int tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

void output_array(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i != n - 1) printf(" ");
    }
}