#include <math.h>
#include <stdio.h>

#define _USE_MATH_DEFINES
#define INTERVAL_COUNT 41
#define X_SCALE 42
#define Y_SCALE 21

double square_hyperbola(double x);
double witchOfAgnesi(double x);
double lemniscateOfBernoulli(double x);
void drawGraph(double (*function)(double x));

int main(void) {
    printf("График Верзьера Аньези:\n");
    drawGraph(witchOfAgnesi);
    
    printf("\nЛемниската Бернулли:\n");
    drawGraph(square_hyperbola);
    
    printf("\nКвадратичная гипербола\n");
    drawGraph(lemniscateOfBernoulli);
    
    return 0;
}

void drawGraph(double (*function)(double x)) {
    for (int row = 0; row < Y_SCALE; row++) {
        for (int col = 0; col < X_SCALE; col++) {
            double x = -M_PI + (2 * M_PI / X_SCALE) * col;
            double y = function(x);

            if (row == Y_SCALE / 2) {
                printf("-");
            } else if (col == X_SCALE / 2) {
                printf("|");
            } else if (row == Y_SCALE / 2 - (int)(Y_SCALE * y)) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

double square_hyperbola(double x) {
    return 1 / (x * x);
}

double witchOfAgnesi(double x) {
    return 1 / (1 + x * x);
}

double lemniscateOfBernoulli(double x) {
    return (sqrt(1 + 4 * x * x) - x * x - 1 < 0) ? 1 : sqrt(sqrt(1 + 4 * x * x) - x * x - 1);
}
