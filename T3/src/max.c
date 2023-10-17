#include <stdio.h>

#define OK 0
#define ERR 1

#define IS_INT(x) (x == (int)x)

void find_max(int num1, int num2);

int main() {
    int num1, num2;
    int status = OK;
    char garbage;

    if(scanf("%d %d%c", &num1, &num2, &garbage) == 3 && garbage == '\n' && IS_INT(num1) && IS_INT(num2)){
        find_max(num1, num2);
    } else {
        status = ERR;
        printf("n/a");
    }

    return status;
}

void find_max(int num1, int num2){
    (num1 > num2) ? printf("%d", num1) : printf("%d", num2);
}