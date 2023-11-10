#include <stdio.h>
#include <stdlib.h>

void allocate(int*** arr, int n){
    (*arr) = malloc(sizeof(int*) * n);
    for(int i = 0; i < n; ++i){
        (*arr)[i] = malloc(sizeof(int) * n);
    }
}

void freeMem(int*** arr, int n){
    for(int i = 0; i < n; ++i){
        free((*arr)[i]);
    }

    free(*arr);
}

void intput(int** arr, int n){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            scanf("%d", &arr[i][j]);
        }
    }
}

void mulmatrix(int** arr1, int** arr2, int** res, int n){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; ++k){
                res[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }
}

void output(int** arr, int n){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            printf("%d", arr[i][j]);
            if(j < n -1){
                printf(" ");
            }
        }
        if(i < n - 1){
            printf("\n");
        }
    }
}


int main(){
    int n;
    int** matrix1;
    int** matrix2;
    int** res;
    scanf("%d", &n);
    allocate(&matrix1, n);
    allocate(&matrix2, n);
    allocate(&res, n);
    intput(matrix1, n);
    intput(matrix2, n);
    mulmatrix(matrix1, matrix2, res, n);
    output(res, n);
    freeMem(&matrix1, n);
    freeMem(&matrix2, n);
    freeMem(&res, n);
}