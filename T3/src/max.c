#include <stdio.h>

#define IS_INT(x) (x == (int)x)

int find_max(int a, int b);

int main(){
    float a, b;

    if(scanf("%f %f", &a, &b) != 2){
        printf("n/a");
        return 1;
    }

    if(!(IS_INT(a) && IS_INT(b))){
        printf("n/a");
        return 1;
    }

    find_max(a, b);
    return 0;
    
}

int find_max(int a, int b){
    if(a >= b){
        printf("%d", a);
    } else {
        printf("%d", b);
    }

    return 0;
}