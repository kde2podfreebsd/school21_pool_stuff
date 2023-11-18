#include <stdio.h>
#define NMAX 10

void input(int *a, int *n, int *error);
void output(int *a, int n);
void squaring(int *a, int n);

int main() {
    int n, data[NMAX];
    int error = 0;

    input(data, &n, &error);

    if (!error) {
        squaring(data, n);
        output(data, n);
    } else {
        printf("n/a");
    }

    return 0;
}

void input(int *a, int *n, int *error) {
    char ch;

    scanf("%d%c", n, &ch);
    if (ch != '\n' || *n <= 0 || *n > NMAX) {
        *error = 1;
    } else {
        for (int i = 0; i < *n; i++) {
            scanf("%d%c", &a[i], &ch);
            if ((i == *n - 1 && ch != '\n') || (i < *n - 1 && ch != ' ' && ch != '\n')) {
                *error = 1;
                break;
            }
        }
    }
}

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i != n - 1) printf(" ");
    }
}

void squaring(int *a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] *= a[i];
    }
}