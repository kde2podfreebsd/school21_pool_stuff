#include <math.h>
#include <stdio.h>

#define _USE_MATH_DEFINES
#define INTERVAL_COUNT 41

double square_hyperbola(double x);
double witchOfAgnesi(double x);
double lemniscateOfBernoulli(double x);


int main(void){
    for(int i = 0; i <= INTERVAL_COUNT; i++){
        double current_value = -M_PI + (2 * M_PI / 41) * i;
        printf("%.7f | %.7f | ", current_value, witchOfAgnesi(current_value));
        (lemniscateOfBernoulli(current_value) == 1) ? printf("- |") : printf("%.7f | ", lemniscateOfBernoulli(current_value));
        printf("%.7f\n", square_hyperbola(current_value));
    }
}

double square_hyperbola(double x){
    return 1 / (x * x);
}

double witchOfAgnesi(double x) {
	return 1/(1 + x * x);
}

double lemniscateOfBernoulli(double x) {
    return (sqrt(1 + 4 * x * x) - x * x - 1 < 0) ? 1 : sqrt(sqrt(1 + 4 * x * x) - x * x - 1);
}
