#include <stdio.h>
#include <stdlib.h>

void input(int* v, int n);
int scalar(int* v1, int* v2, int n);

int main(){
    int* v1;
    int* v2;
    int n;

    scanf("%d", &n);

    if(n <=0){
        printf("n/a");
        return 1; 
    }

    v1 = calloc(n, sizeof(int));
    v2 = calloc(n, sizeof(int));

    if(v1 == NULL || v2 == NULL){
        printf("n/a");
        free(v1);
        free(v2);
        return 1;
    }

    input(v1, n);
    input(v2, n);

    printf("%d", scalar(v1, v2, n));
}

void input(int* v, int n) {
    for(int i =0; i < n; ++i){
        scanf("%d", &v[i]);
    }
}

int scalar(int* v1, int* v2, int n){
    int mul = 0;
    for(int i = 0; i < n; ++i){
        mul += v1[i]* v2[i];
    }

    return mul;
}