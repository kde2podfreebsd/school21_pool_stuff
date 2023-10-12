#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main()
{
    int n, data[NMAX];
    if(input(data, &n) == 1){
        printf("n/a");
        return 1;
    }
    output(data, n);
    output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));

    return 0;
}

int input(int *a, int *n){
    char garbage;
    if(scanf("%d%c", n, &garbage) == 2 && garbage == '\n'){
        if((*n > NMAX) || (*n <= 0)){
            return 1;
        }
    } else {
        return 1;
    }

    for(int *p = a; p - a < *n; p++){
        if(scanf("%d%c", p, &garbage) == 2 && garbage == '\n'){} else {
            return 1;
        }
    }

    return 0;
}

void output(int *a, int n){
    for(int *p = a; p - a < n; p++){
        printf("%d ", *p);
    }
}

int max(int *a, int n){
    for(int *p = a; p - a < n; p++){
        if(p == a){
            max = *p;
        }
        if(*p > max){
            max = *p;
        }
    }

    return max;
}

int min(int *a, int n){
    for(int *p = a; p - a < n; p++){
        if(p == a){
            min = *p;
        }
        if(*p < min){
            min = *p;
        }
    }

    return min;
}

double mean(int *a, int n){
    int sum = 0;
    for(int *p = a; p - a < n; p++){
        sum += *p;
    }
    return (double)sum / n;
}

double variance(int *a, int n){
    double sum_square_diff = 0;
    for(int *p = a; p - a < n; p++){
        sum_square_diff += (*p - mean(a, n)) * (*p - mean(a,n));
    }

    return sum_square_diff / (double)n;
}