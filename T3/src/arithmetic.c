#include <stdio.h>

#define IS_INT(x) (x == (int)x)

int sum(int a, int b){
    int sum = a + b;
    int diff = a - b;
    int com = a * b;
    // float del;
    int del;
    if(b==0){
        printf("%d %d %d n/a", sum, diff, com);
    } else {
        del = a / b;
        printf("%d %d %d %d", sum, diff, com, del);
    }
    return 0;
}

int main(){
    int a, b;

    if(scanf("%d %d", &a, &b) != 2) {
        printf("n/a");
        return 1;
    }

    // if(!(IS_INT(a) && IS_INT(b))){
    //     printf("n/a");
    //     return 1;
    // }
    //??? зачем это есть в решении? 
    // char c = ' ';
    // if ((scanf("%c", &c) != 0) && (c != '\n')) {
    //     printf("n/a");
    //     return 1;
    // }

    sum(a, b);
    return 0;
}