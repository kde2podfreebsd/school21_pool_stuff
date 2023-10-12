#include <stdio.h>
#include <math.h>

#define INTERVAL_COUNT 41

double square_hyperbola(double x){
    return 1 / (x * x);
}

double witchOfAgnesi(double x) {
	return 1/(1 + x * x);
}

double lemniscateOfBernoulli(double x) {
    return (sqrt(1 + 4 * x * x) - x * x - 1 < 0) ? 1 : sqrt(sqrt(1 + 4 * x * x) - x * x - 1);
}

int main(void){
    for(int i = 0; i <= INTERVAL_COUNT; i++){
        double current_value = -M_PI + i * ((M_PI - (-M_PI)) / (double)INTERVAL_COUNT);
        printf("%.7lf | %.7lf | ", current_value, witchOfAgnesi(current_value));
        (lemniscateOfBernoulli(current_value) == 1) ? printf("- |") : printf("%.7lf | ", lemniscateOfBernoulli(current_value));
        printf("%.7lf\n", square_hyperbola(current_value));
    }
}