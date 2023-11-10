#include <stdio.h>

int main(){
    int n;
    int result = 0;
    scanf("%d", &n);

    if(n < 0){
        n = -n;
    }

    while(n > 0){
        int temp = n % 10;
        if((temp % 2) == 1){
            result = (result == 0 ? 1 : result) * temp;
        }
        n /= 10;
    }

    printf("%d", result);
}