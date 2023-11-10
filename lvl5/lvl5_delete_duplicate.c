#include <stdio.h>
#include <stdlib.h>

int input(int** arr){
    int temp;
    int size = 0;

    while(scanf("%d", &temp) == 1 && temp > -1){
        if(size == 0){
            size++;
            *arr = malloc(sizeof(int) * size);
            (*arr)[size-1] = temp;
        } else{
            size++;
            *arr = realloc(*arr, sizeof(int) * size);
            (*arr)[size-1] = temp;
        }
    }

    return size;
}

int delete(int* arr, int size){
    for(int i = 0; i < size; ++i){
        for(int j = i + 1; j < size;){
            if(arr[i] == arr[j]){
                for(int k = j; k < size - 1; ++k){
                    arr[k] = arr[k+1];
                }
                size--;
            } else {
                j++;
            }
        }
    }

    return size;
}

void output(int* array, int size){
    for(int i = 0; i < size; ++i){
        printf("%d", array[i]);
        if(i < size-1){
            printf(" ");
        }
    }
}

int main(){
    int* arr;
    int size = input(&arr);
    size = delete(arr, size);
    output(arr, size);
    free(arr);
}