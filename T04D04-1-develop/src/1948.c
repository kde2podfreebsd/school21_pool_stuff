#include <stdio.h>

int find_max_prime_divisor(int number);
int div(int a, int b);

int main() {
    int a;
    if (scanf("%d", &a)) {
        if (a < 0) a *= -1;
        if (a < 2)
            printf("n/a");
        else
            printf("%d", find_max_prime_divisor(a));
    } else
        printf("n/a");
}

int find_max_prime_divisor(int number) {
    int max_prime_divisor = 2;

    while (max_prime_divisor != number) {
        int div_result = div(number, max_prime_divisor);
        if (div_result * max_prime_divisor == number)
            number = div_result;
        else
            max_prime_divisor += 1;
    }

    return max_prime_divisor;
}

int div(int a, int b) {
    int counter = 0;
    while (a > 0) {
        a -= b;
        if (a >= 0) counter += 1;
    }
    return counter;
}