#include <stdio.h>

#define OK 0
#define ERR 1

int fibonacci(int n){
    return n < 2 ? n : fibonacci(n-2) + fibonacci(n-1);
}

int main(){
    int n;
    char garbage;
    int status = OK;
    if(scanf("%d%c", &n, &garbage) == 2 && garbage == '\n' && n > 0){
        n = fibonacci(n);
        printf("%d", n);
    } else {
        status = ERR;
        printf("n/a");
    }

    return status;
}