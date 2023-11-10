#include <stdio.h>
#include <stdlib.h>

int input(int** arr);
void output(int* arr, int size);

int main(){
    int* arr;
    int size = input(&arr);
    output(arr, size);
}

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

void output(int* arr, int size){
    for(int i = size - 1; i >= 0; --i){
        printf("%d", arr[i]);
        if(i > 0){
            printf(" ");
        }
    }
}