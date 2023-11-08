#include <stdio.h>
#include <stdlib.h>

#define ERR 0
#define OK 1

int input(int** array);
void output(int* array, int size);
void deleteDuplicate(int* array, int* size);

int main(){
    int* array;
    int size;
    size = input(&array);
    deleteDuplicate(array, &size);

    array = realloc(array, sizeof(int) * size);

    output(array, size);

    free(array);
}

int input(int** array){
    int temp;
    int size = 0;

    while(scanf("%d", &temp) == 1 && temp > -1){
        if(size == 0){
            size++;
            *array = malloc(sizeof(int) * size);
            (*array)[size-1] = temp;
        } else{
            size++;
            *array = realloc(*array, sizeof(int) * size);
            (*array)[size-1] = temp;
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

void deleteDuplicate(int* array, int* size) {
    for (int i = 0; i < *size; ++i) {
        for (int j = i + 1; j < *size;) {
            if (array[i] == array[j]) {
                for (int k = j; k < *size - 1; ++k) {
                    array[k] = array[k + 1];
                }
                (*size)--;
            } else {
                j++; 
            }
        }
    }
}