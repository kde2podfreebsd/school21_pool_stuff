#include <stdio.h>

int main(){
    float x, y;

    if(scanf("%f %f", &x, &y) != 2){
        printf("n/a");
        return 1;
    }

    if(x*x + y*y < 25){
        printf("GOTCHA");
    } else{
        printf("MISS");
    }

    return 0;
}