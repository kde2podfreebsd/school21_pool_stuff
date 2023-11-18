#include <stdio.h>
#define NMAX 10

int input_array(int *a, int n);
void copy_array(const int *a, int *b, int n);
void quicksort_hoar(int *a, int l, int r);
int hoar_partition(int *a, int l, int r);
void heapSort(int *a, int n);
void sieveDown(int *a, int root, int bottom);
void output_array(int *a, int n);
void swap(int *a, int *b);

int main() {
    int n = NMAX, data[NMAX];
    int error;

    error = input_array(data, n);

    if (!error) {
        int data_copy[NMAX];
        copy_array(data, data_copy, n);

        quicksort_hoar(data, 0, n - 1);
        heapSort(data_copy, n);
        output_array(data, n);
        printf("\n");
        output_array(data_copy, n);
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

void copy_array(const int *a, int *b, int n) {
    for (int i = 0; i < n; i++) {
        b[i] = a[i];
    }
}

void quicksort_hoar(int *a, int l, int r) {
    if (l < r) {
        int q = hoar_partition(a, l, r);
        quicksort_hoar(a, l, q);
        quicksort_hoar(a, q + 1, r);
    }
}

int hoar_partition(int *a, int l, int r) {
    int pivot = a[(l + r) / 2];
    int i = l, j = r;
    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;
        if (i >= j) break;
        swap(&a[i], &a[j]);
        i++;
        j--;
    }
    return j;
}

void heapSort(int *a, int n) {
    for (int i = n / 2; i >= 0; i--) {
        sieveDown(a, i, n - 1);
    }
    for (int i = n - 1; i >= 1; i--) {
        swap(&a[0], &a[i]);
        sieveDown(a, 0, i - 1);
    }
}

void sieveDown(int *a, int root, int bottom) {
    int maxChild;
    int done = 0;
    while ((root * 2 <= bottom) && (!done)) {
        if (root * 2 == bottom)
            maxChild = root * 2;
        else if (a[root * 2] > a[root * 2 + 1])
            maxChild = root * 2;
        else
            maxChild = root * 2 + 1;

        if (a[root] < a[maxChild]) {
            swap(&a[root], &a[maxChild]);
            root = maxChild;
        } else {
            done = 1;
        }
    }
}

void output_array(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i != n - 1) printf(" ");
    }
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}