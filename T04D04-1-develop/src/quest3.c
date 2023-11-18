#include <math.h>
#include <stdio.h>

int fib(int n);

int main() {
    int n;
    if (scanf("%d", &n)) {
        n < 0 ? printf("%d", (int)pow(-1, n + 1) * fib(n * (-1))) : printf("%d", fib(n));
    } else
        printf("n/a");
    return 0;
}

int fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}