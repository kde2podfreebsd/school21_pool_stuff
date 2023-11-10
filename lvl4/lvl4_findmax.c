#include <stdio.h>

int main(){
    int temp;

    scanf("%d", &temp);

    int max = temp;
    if(temp < 0){
        printf("n/a");
        return 1;
    }

    while(scanf("%d", &temp) == 1 && temp != -1){
        if(temp > max){
            max = temp;
        }
    }

    printf("%d", max);
}