#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846

double get_verzier_aniezi(double x);
double get_lemniskata_bernulli(double x);
double get_sqr_hyperbola(double x);

int main() {
    double STEP = PI * 2 / 41;
    double x = -PI;
    for (int i = 1; i <= 42; i++) {
        double y_va = get_verzier_aniezi(x);
        double y_lb = get_lemniskata_bernulli(x);
        double y_sh = get_sqr_hyperbola(x);

        printf("%.7lf|", x);
        printf("%.7lf|", y_va);
        y_lb > 0 ? printf("%.7lf|", y_lb) : printf("-|");
        printf("%.7lf\n", y_sh);

        x += STEP;
    }
}

double get_verzier_aniezi(double x) { return 1 / (1 + x * x); }

double get_lemniskata_bernulli(double x) {
    double under_root = sqrt(1 + 4 * x * x) - x * x - 1;
    return under_root > 0 ? sqrt(under_root) : -1;
}

double get_sqr_hyperbola(double x) { return 1 / (x * x); }