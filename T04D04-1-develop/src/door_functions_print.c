#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846
#define X_SEGMENT 0.5

double get_verzier_aniezi(double x);
double get_lemniskata_bernulli(double x);
double get_sqr_hyperbola(double x);

void plot(double (*func)());
void print_divide_line();

int main() {
    plot(get_verzier_aniezi);
    print_divide_line();
    plot(get_lemniskata_bernulli);
    print_divide_line();
    plot(get_sqr_hyperbola);
}

double get_verzier_aniezi(double x) { return 1 / (1 + x * x); }

double get_lemniskata_bernulli(double x) {
    double under_root = sqrt(1 + 4 * x * x) - x * x - 1;
    return under_root > 0 ? sqrt(under_root) : -1;
}

double get_sqr_hyperbola(double x) { return 1 / (x * x); }

void plot(double (*func)()) {
    double STEP = PI * 2 / 41;
    double x = -PI;
    int pos_x = 0;
    double y_min, y_max;

    y_min = y_max = (*func)(-PI);
    for (int i = 2; i <= 42; i++) {
        x += STEP;
        double y = (*func)(x);
        if (y < y_min) y_min = y;
        if (y > y_max) y_max = y;
    }
    x = -PI;

    for (int row = 0; row <= 42; row++) {
        double y = (*func)(x);
        int x_axes_length = (int)(21 / X_SEGMENT);
        int x_axes_segment = (int)(1 / X_SEGMENT);
        double y_corr = round((y / y_max) * x_axes_length);

        for (int col = 0; col <= x_axes_length; col++) {
            if (row == 21) {
                if (col % x_axes_segment != 0)
                    printf("-");
                else
                    printf("|");
                continue;
            }

            if (col == (int)y_corr) {
                printf("*");
                continue;
            } else if (col == 0) {
                printf("|");
                continue;
            } else
                printf(" ");
        }

        printf("\n");

        if (row == 21) continue;

        pos_x += 1;
        x += STEP;
    }
}

void print_divide_line() {
    printf("\n");
    for (int col = 0; col <= (int)(21 / X_SEGMENT); col++) {
        printf("=");
    }
    printf("\n\n");
}