/*
    Search module for the desired value from data array.

    Returned value must be:
        - "even"
        - ">= mean"
        - "<= mean + 3 * sqrt(variance)"
        - "!= 0"

        OR

        0
*/

#include <math.h>
#include <stdio.h>
#define NMAX 30

int input(int *a, int *n);
double mean(int const *a, int n);
double variance(int *a, int n);

int search(int *a, int n);

int main() {
    int n, data[NMAX];
    int error;

    error = input(data, &n);

    if (!error) {
        printf("%d", search(data, n));
    } else {
        printf("n/a");
    }

    return 0;
}

int input(int *a, int *n) {
    char ch;
    int error = 0;

    scanf("%d%c", n, &ch);
    if (ch != '\n' || *n <= 0 || *n > NMAX) {
        error = 1;
    } else {
        for (int i = 0; i < *n; i++) {
            scanf("%d%c", &a[i], &ch);
            if ((i == *n - 1 && ch != '\n') || (i < *n - 1 && ch != ' ' && ch != '\n')) {
                error = 1;
                break;
            }
        }
    }

    return error;
}

double mean(int const *a, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return (double)sum / n;
}

double variance(int *a, int n) {
    double m = mean(a, n);
    double sum_sqr = 0;
    for (int i = 0; i < n; i++) {
        sum_sqr += pow(a[i] - m, 2);
    }
    return sum_sqr / n;
}

int search(int *a, int n) {
    int desired_number = 0;
    double m = mean(a, n);
    double v = variance(a, n);
    double three_sigm = m + 3 * sqrt(v);

    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0 && a[i] >= m && a[i] <= three_sigm && a[i] != 0) {
            desired_number = a[i];
            break;
        }
    }
    return desired_number;
}