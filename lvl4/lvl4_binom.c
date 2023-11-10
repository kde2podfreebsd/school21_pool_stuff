#include <stdio.h>

int factorial(int n){
    if(n == 0 || n == 1){
        return 1;
    }

    int factorial = 1;

    for(int i = 1; i <= n; ++i){
        factorial *= i;
    }

    return factorial;

}

int main(){
    int n;
    scanf("%d", &n);
    for(int i = 0; i <=n; ++i){
        printf("%d", factorial(n)/(factorial(i) * factorial(n - i)));
        if(i < n){
            printf(" ");
        }
    }
}