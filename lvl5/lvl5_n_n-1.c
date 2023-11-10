#include <stdio.h>
#include <stdlib.h>

int input(int** arr);

int main(){
    int* arr;
    int size = input(&arr);
    for(int i = 0; i < size / 2; ++i){
        printf("%d %d", arr[i], arr[size-i-1]);
        if(i < size / 2 - 1){
            printf(" ");
        }
    }
    if(size%2 == 1){
        printf(" %d", arr[size/2]);
    }
}

int input(int** arr) {
    int temp;
    int size = 0;
    while(scanf("%d", &temp) == 1 && temp > -1){
        if(size == 0){
            size++;
            *arr = malloc(sizeof(int) * size);
            (*arr)[size-1] = temp; 
        } else {
            size++;
            *arr = realloc(*arr, size);
            (*arr)[size-1] = temp; 
        }
    }

    return size;
}