#include <stdio.h>

#define NMAX 30
#define is_even(x) ((x%2==0) ? 1 : 0)

int input(int *array, int *n);
double mean(int *array, int n);
double variance(int *array, int n);
int is_3sigma_rule(int *array, int n, int x);
int search(int *array, int n);


int main(){
    int n, data[NMAX];
    if(input(data, &n) == 1){
        printf("n/a");
        return 1;
    }

    printf("%d", search(data, n));

}

int input(int *array, int *n){
    char garbage;
    if(scanf("%d%c", n, &garbage) == 2 && garbage == '\n'){
        if((*n > NMAX) || (*n <= 0)){
            return 1;
        }
    } else {
        return 1;
    }

    for(int *p = array; p - array < *n; p++){
        if(scanf("%d%c", p, &garbage) == 2 && garbage == '\n'){} else {
            return 1;
        }
    }

    return 0;
}

double mean(int *array, int n){
    int sum = 0;
    for(int *p = array; p - array < n; p++){
        sum += *p;
    }
    return (double)sum / n;
}

double variance(int *array, int n){
    double sum_square_diff = 0;
    for(int *p = array; p - array < n; p++){
        sum_square_diff += (*p - mean(array, n)) * (*p - mean(array,n));
    }

    return sum_square_diff / (double)n;
}

int is_3sigma_rule(int *array, int n, int x){

    int mean_value = mean(array, n);
    int std_dev = variance(array, n);
    
    double lowerLimit = mean_value - 3 * std_dev;
    double upperLimit = mean_value + 3 * std_dev;

    if (x >= lowerLimit && x <= upperLimit) {
        return 1;
    } else {
        return 0;
    }
}

int search(int *array, int n){
    int desired_number = 0;
    
    for(int *p = array; p - array < n; p++){
        if(is_even(*p) && *p >= mean(array, n) && *p != 0 && is_3sigma_rule(array, n, *p)){
            desired_number = *p;
        }
    }

    return desired_number;
}