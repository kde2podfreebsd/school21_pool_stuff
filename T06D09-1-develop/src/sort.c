#include <stdio.h>
#define NMAX 10

int input_array(int *a, int n);
void sort(int *a, int n);
void output_array(int *a, int n);

int main() {
    int n = NMAX, data[NMAX];
    int error;

    error = input_array(data, n);

    if (!error) {
        sort(data, n);
        output_array(data, n);
    } else {
        printf("n/a");
    }

    return 0;
}

int input_array(int *a, int n) {
    int error = 0;

    for (int i = 0; i < n; i++) {
        if (!scanf("%d", &a[i])) {
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