#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 10
#define OK 0
#define ERR 1

int allocate(int **m, int *n);
void output(int *a);
void swap(int *a, int *b);
void quickSort(int *arr, int j);

int main(){
    int *m = NULL;
    int n = 0;
    if(allocate(&m, &n) == 1){
        printf("n/a");
        return 1;
    }
    quickSort(m, n-1);
    output(m);

    return 0;
}

int allocate(int **m , int *n){
    int status = OK;
    if(scanf("%d", n) == 1 && *n > 0){
        *m = (int*)malloc((*n) * sizeof(int));
        if(m == NULL){
            status = ERR;
        }

        char garbage;
        for(int i = 0; i < *n; i++){
            if(scanf("%d%c", &(*m)[i], &garbage) == 2 && garbage == '\n'){
                status = OK;
            } else {
                free(*m);
                status = ERR;
                *m = NULL;
            }
        }
    }

    return status;
}

void output(int *a){
    for(int *p = a; p - a < ARR_SIZE; p++){
        printf("%d ", *p);
    }
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(int *array, int right_iterator){
    int arr_size = right_iterator;
    int left_iterator = 0;
    int pivot = array[(int)(right_iterator/2)];
    do {
        while(array[left_iterator] < pivot) left_iterator++;
        while(array[right_iterator] > pivot) right_iterator--;

        if (left_iterator <= right_iterator){
            swap(&array[left_iterator], &array[right_iterator]);
            left_iterator++;
            right_iterator--;
        }

    } while(left_iterator <= right_iterator);

    if (right_iterator > 0) quickSort(array, right_iterator);
    if (arr_size > left_iterator) quickSort(array+left_iterator, arr_size-left_iterator);
}