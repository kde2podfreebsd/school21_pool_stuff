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
        for(int j = m-1; j >= 0; j--){
            printf("%d", arr[i][j]);
            if(j < m -1){
                printf(" ");
            }
        }
        if(i < n - 1){
            printf("\n");
        }
    }
}

void transponed(int** arr, int** res, int n, int m){
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            res[j][i] = arr[i][j];
        }
    }
}

int main() {
    int n;
    int m;
    int** matrix1;
    int** res;

    scanf("%d %d", &n, &m);
    allocate(&matrix1, n, m);
    allocate(&res, m, n); 
    intput(matrix1, n, m);
    transponed(matrix1, res, n, m);
    output(res, m, n);
    freeMem(&matrix1, n);
    freeMem(&res, m); 
    return 0;
}