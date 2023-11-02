#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 10
#define OK 1
#define ERR 0

int allocate(int **m, int *n);
void output(int *a);
void swap(int *a, int *b);
void quickSort(int *arr, int j);

int main() {
    int *m = NULL;
    int n;

    if (allocate(&m, &n) == 0) {
        printf("n/a");
        return 1;
    }
    quickSort(m, ARR_SIZE - 1);
    output(m);

    return 0;
}

int allocate(int **m, int *n) {
    int flag = OK;
    if (scanf("%d", n) == 1 && *n > 0) {
        *m = (int *)malloc(*n * sizeof(int));
        if (!m) {
            flag = ERR;
        } else {
            for (int i = 0; i < *n; i++) {
                if (scanf("%d", &(*m)[i]) != 1) {
                    flag = ERR;
                    *m = NULL;
                }
            }
        }
        free(*m);
    }

    return flag;
}

void output(int *a) {
    for (int *p = a; p - a < ARR_SIZE; p++) {
        printf("%d", *p);
        if (p - a < ARR_SIZE - 1) {
            printf(" ");
        }
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(int *array, int right_iterator) {
    int arr_size = right_iterator;
    int left_iterator = 0;
    int pivot = array[(int)(right_iterator / 2)];
    do {
        while (array[left_iterator] < pivot) left_iterator++;
        while (array[right_iterator] > pivot) right_iterator--;

        if (left_iterator <= right_iterator) {
            swap(&array[left_iterator], &array[right_iterator]);
            left_iterator++;
            right_iterator--;
        }

    } while (left_iterator <= right_iterator);

    if (right_iterator > 0) quickSort(array, right_iterator);
    if (arr_size > left_iterator) quickSort(array + left_iterator, arr_size - left_iterator);
}
