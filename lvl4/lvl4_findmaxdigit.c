#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int max = 0;
    while(n > 0){
        int temp = n % 10;
        n /= 10;
        if(temp > max){
            max = temp;
        }
    }

    printf("%d", max);
}