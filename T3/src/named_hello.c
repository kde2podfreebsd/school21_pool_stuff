#include <stdio.h>

#define OK 0
#define ERR 1

int main() {
    int num;
    char garbage;
    int status = OK;
    if(scanf("%d%c", &num, &garbage) == 2 && garbage == '\n'){
        printf("Hello, %d!", num); 
    } else {
        status = ERR;
    }

    return status;
}
