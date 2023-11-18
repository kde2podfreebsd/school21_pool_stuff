#include <stdio.h>

int max(int a, int b);

int main() {
    int a, b;
    if (scanf("%d %d", &a, &b) == 2) {
        printf("%d", max(a, b));
    } else
        printf("n/a");
    return 0;
}

int max(int a, int b) {
    if (a >= b) return a;
    return b;
}