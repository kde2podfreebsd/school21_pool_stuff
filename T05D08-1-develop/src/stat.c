#include <math.h>
#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int const *a, int n);
int max(int const *a, int n);
int min(int const *a, int n);
double mean(int const *a, int n);
double variance(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    int error;

    error = input(data, &n);

    if (!error) {
        output(data, n);
        output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));
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

void output(int const *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
}

int max(int const *a, int n) {
    int max_v = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max_v) max_v = a[i];
    }
    return max_v;
}

int min(int const *a, int n) {
    int min_v = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < min_v) min_v = a[i];
    }
    return min_v;
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

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6lf %.6lf", max_v, min_v, mean_v, variance_v);
}
