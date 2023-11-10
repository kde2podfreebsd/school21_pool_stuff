#include <stdio.h>
#include <stdlib.h>

void allocate(int*** arr, int n, int m){
    (*arr) = malloc(sizeof(int*) * n);
    for(int i = 0; i < n; ++i){
        (*arr)[i] = malloc(sizeof(int) * m);
    }
}

void freeMem(int*** arr, int n){
    for(int i = 0; i < n; ++i){
        free((*arr)[i]);
    }

    free(*arr);
}

void intput(int** arr, int n, int m){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            scanf("%d", &arr[i][j]);
        }
    }
}

void output(int** arr, int n, int m){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
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

int findmax(int** arr, int n, int m){
    int max = arr[0][0];
    int index = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if(arr[i][j] > max){
                max = arr[i][j];
                index = i;
            }
        }
    }

    return index;
}

int findmin(int** arr, int n, int m){
    int min = arr[0][0];
    int index = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            if(arr[i][j] < min){
                min = arr[i][j];
                index = i;
            }
        }
    }
    return index;
}

void swap(int** arr, int index1, int index2){
    int* temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}

int main(){
    int n;
    int m;
    int** matrix1;
    scanf("%d %d", &n, &m);
    allocate(&matrix1, n, m);
    intput(matrix1, n, m);
    int index1 = findmax(matrix1, n, m);
    int index2 = findmin(matrix1, n, m);
    swap(matrix1, index1, index2);
    output(matrix1, n, m);
    freeMem(&matrix1, n);
}