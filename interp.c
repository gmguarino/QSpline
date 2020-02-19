#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "QSpline.h"
#define M_PI 3.14159265358979323846
#define LEN 12
#define UPSAMPLE_RATIO 10

double gaussian(double x, double mu, double sigma);

int main()
{
    double x[LEN], y[LEN];
    double x_up[(LEN - 1) * UPSAMPLE_RATIO + 1];
    double y_up[(LEN - 1) * UPSAMPLE_RATIO + 1];

    
    double mu = 1.5, sigma = 0.2;
    double start = 0, stop = 3;
    double delta = (stop - start) / (LEN - 1);
    printf("Step size : %lf\n", delta);
    printf("Undersampled data:\n");
    FILE *fp = fopen("undersampled.dat", "w+");
    for (size_t i = 0; i < LEN; i++)
    {
        x[i] = start + i * delta;
        y[i] = gaussian(x[i], mu, sigma);
        fprintf(fp, "%lf\t %lf\n", x[i], y[i]);
        printf("%lf\t %lf\n", x[i], y[i]);
    }
    printf("\n");
    fclose(fp);

    spline_interpolation(x, y, x_up, y_up, LEN, UPSAMPLE_RATIO);
    fp = fopen("interpolated.dat", "w+");
    printf("Interpolated Data:\n");
    for (size_t i = 0; i < (LEN - 1) * UPSAMPLE_RATIO + 1; i++)
    {
        fprintf(fp, "%lf\t %lf\n", x_up[i], y_up[i]);
        printf("%lf\t %lf\n", x_up[i], y_up[i]);
    }
    fclose(fp);

}

double gaussian(double x, double mu, double sigma)
{
    double g;
    g = exp( - 1 * pow(x - mu, 2.) / (2 * pow(sigma, 2.)));
    return g;
}