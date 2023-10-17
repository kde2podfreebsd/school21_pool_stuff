#include <stdio.h>
#include <math.h>

#define OK 0
#define ERR 1

void important_function(float x);

int main(){
    float num;
    int status = OK;
    char garbage;

    if(scanf("%f%c", &num, &garbage) == 2 && garbage == '\n') {
        important_function(num);
    } else {
        status = ERR;
        printf("n/a");
    }

    return status;
}

void important_function(float x){
    double y = 7e-3 * pow(x, 4) + ((22.8 * pow(x, 1/3) - 1e3) * x + 3) / (x * x / 2) - x * pow((10 + x), (2/x)) - 1.01;
    printf("%.1lf", y);
}