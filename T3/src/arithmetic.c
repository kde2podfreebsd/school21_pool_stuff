#include <stdio.h>

#define OK 0
#define ERR 1

void calculate(int num1, int num2);

int main() {
    int num1, num2;
    char garbage;
    int status = OK;
    if(scanf("%d %d%c", &num1, &num2, &garbage) == 3 && garbage == '\n'){
        calculate(num1, num2);
    } else {
        status = ERR;
        printf("n/a");
    }

    return status;
}

void calculate(int num1, int num2){
    (num2==0) ? printf("%d %d %d n/a", num1 + num2, num1 - num2, num1 * num2) : printf("%d %d %d %d", num1 + num2, num1 - num2, num1 * num2, num1/num2);
}
