#include <stdio.h>

#define NMAX 10

void input(int *buffer, int *length, int *shift, int *error);
void output(const int *buffer, int length);
void cycle_shift_left(int *buffer, int length);
void swap(int *a, int *b);

int main() {
    int n, data[NMAX];
    int shift;
    int error = 0;

    input(data, &n, &shift, &error);

    if (!error) {
        if (shift < 0) shift = n + shift;
        for (int i = 1; i <= shift; i++) {
            cycle_shift_left(data, n);
        }
        output(data, n);
    } else
        printf("n/a");

    return 0;
}

void input(int *buffer, int *length, int *shift, int *error) {
    if (!scanf("%d", length) || *length <= 0 || *length > NMAX) {
        *error = 1;
    } else {
        for (int i = 0; i < *length; i++) {
            if (!scanf("%d", &buffer[i])) {
                *error = 1;
                return;
            }
        }
        if (!scanf("%d", shift)) *error = 1;
    }
}

void output(const int *buffer, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d", buffer[i]);
        if (i != length - 1) printf(" ");
    }
}

void cycle_shift_left(int *buffer, int length) {
    int tmp = buffer[0];
    for (int i = 1; i < length; i++) {
        swap(&buffer[i - 1], &buffer[i]);
    }
    buffer[length - 1] = tmp;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}