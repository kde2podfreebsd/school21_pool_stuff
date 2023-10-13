#include <stdio.h>

#define ARR_SIZE 10

int input(int *a);
void output(int *a);
void swap(int *a, int *b);
void quickSort(int *arr, int j);

int main(){
    int data[ARR_SIZE];
    if(input(data) == 1){
        printf("n/a");
        return 1;
    }
    quickSort(data, ARR_SIZE-1);
    output(data);

    return 0;
}

int input(int *a){
    char garbage;
    for(int *p = a; p - a < ARR_SIZE; p++){
        if(scanf("%d%c", p, &garbage) == 2 && garbage == '\n'){} else {
            return 1;
        }
    }

    return 0;
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