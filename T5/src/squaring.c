#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main()
{
    int n, data[NMAX];
    if(input(data, &n) == 1){
        printf("n/a");
        return 1;
    }
    squaring(data, n);
    output(data, n);

    return 0;
}

int input(int *a, int *n){
    char garbage;
    if(scanf("%d%c", n, &garbage) == 2 && garbage == '\n'){
        if((*n > NMAX) || (*n <= 0)){
            return 1;
        }
    } else {
        return 1;
    }

    for(int *p = a; p - a < *n; p++){
        if(scanf("%d%c", p, &garbage) == 2 && garbage == '\n'){} else {
            return 1;
        }
    }

    return 0;
}

void output(int *a, int n){
    for(int *p = a; p - a < n; p++){
        printf("%d", *p);

        if(p - a != n-1){
            printf(" ");
        }
    }
}

void squaring(int *a, int n){
    for(int *p = a; p - a < n; p++){
        *p = *p * *p;
    }
}
