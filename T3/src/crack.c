#include <stdio.h>

#define OK 0
#define ERR 1

void is_in_circle(double x, double y);

int main(){
    double x, y;
    int status = OK;
    char garbage;
    
    if(scanf("%lf %lf%c", &x, &y, &garbage) == 3 && garbage == '\n'){
        is_in_circle(x, y);
    } else {
        status = ERR;
        printf("n/a");
    }

    return status;
}

void is_in_circle(double x, double y){
    (x*x + y*y < 25) ? printf("GOTCHA") : printf("MISS");
}