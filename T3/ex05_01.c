#include <stdio.h>
#include <stdlib.h>

void inputVector(int* vector, int size);
int mulVectors(int* vector1, int* vector2, int size);

int main(){
    int* vector1;
    int* vector2;
    int size = 0;

    if(scanf("%d", &size) != 1 || size <= 0){
        printf("n/a");
        return 1;
    }

    vector1 = (int*)calloc(size, sizeof(int));
    vector2 = (int*)calloc(size, sizeof(int));
    if(vector1 == NULL || vector2 == NULL){
        printf("n/a");
        free(vector1);
        free(vector2);
        return 1;
    }

    inputVector(vector1, size);
    inputVector(vector2, size);

    int sum = mulVectors(vector1, vector2, size);
    printf("%d", sum);
}

void inputVector(int* vector, int size){
    for(int i = 0; i < size; ++i){
       scanf("%d", &vector[i]); 
    }
}

int mulVectors(int* vector1, int* vector2, int size){
    int sum = 0;
    for(int i = 0; i < size; ++i){
        sum += vector1[i] * vector2[i];
    }

    return sum;
}