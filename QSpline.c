#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "QSpline.h"



void cubic_spline_coefficients(double x[/*Len*/], double y[/*Len*/], struct coefficients *coeff, int Len){
    int n = Len - 1;
    double steps[n];
    double alpha;
    double l[Len], u[Len], z[Len];
    l[0] = 1;
    u[0] = 0;
    z[0] = 0;

    for(size_t i=0; i < n; i++)
    { 
        steps[i] = x[i+1] - x[i];
        if (i > 0)
        {
            alpha = 3 * (y[i + 1] - y[i]) / steps[i] - 3 * (y[i] - y[i - 1]) / steps[i - 1];
            l[i] = 2 * (x[i + 1] - x[i - 1]) - steps[i - 1] * u[i - 1];
            u[i] = steps[i] / l[i];
            z[i] = (alpha - steps[i - 1]* z[i - 1]) / l[i];
        }
        if (i < n)
            coeff->a[i] = y[i];
    }
    l[n] = 1;
    z[n] = 0;
    double c_n = 0;

    coeff->c[n - 1] = z[n-1] - u[n - 1] * c_n;
    coeff->b[n - 1] = (y[n] - y[n - 1]) / steps[n - 1] - (steps[n - 1] * (c_n + 2 * coeff->c[n - 1])) / 3;
    coeff->d[n - 1] = (c_n - coeff->c[n - 1]) / (3 * steps[n - 1]);
    for (int j = n - 2; j > -1; j--)
    {
        coeff->c[j] = z[j] - u[j] * coeff->c[j + 1];
        coeff->b[j] = (y[j + 1] - y[j]) / steps[j] - steps[j] * (coeff->c[j + 1] + 2 * coeff->c[j]) / 3;
        coeff->d[j] = (coeff->c[j + 1] - coeff->c[j]) / (3 * steps[j]);

    }
}

double spline_interpolation(double x[/*Len*/], double y[/*Len*/], double x_up[/*(Len - 1) * upsample_ratio + 1*/], 
                          double y_up[/*(Len - 1) * upsample_ratio + 1*/], int Len, int upsample_ratio)
{
    
    struct coefficients *coeff;
    double delta;
    double max = -1e10, max_x = 0;
    int count = 0;
    coeff = malloc(sizeof(struct coefficients) + 1);
    coeff->a = malloc(sizeof(double) * (Len - 1) + 1);
    coeff->b = malloc(sizeof(double) * (Len - 1) + 1);
    coeff->c = malloc(sizeof(double) * (Len - 1) + 1);
    coeff->d = malloc(sizeof(double) * (Len - 1) + 1);
    memset(coeff, 0, sizeof(coeff));
    
    cubic_spline_coefficients(x, y, coeff, Len);
    
    for (size_t i = 0; i < Len - 1; i++)
    {
        delta = (x[i + 1] - x[i]) / upsample_ratio;
        for (size_t j = 0; j < upsample_ratio; j++)
        {
            x_up[count] = x[i] + j * delta;
            y_up[count] = coeff->a[i] + coeff->b[i] * (j * delta) + coeff->c[i] * pow((j * delta), 2) + coeff->d[i] * pow((j * delta), 3);
            if (y_up[count] > max)
            {
                max = y_up[count];
                max_x = x_up[count];
            }
            count++;
        }    
    }
    x_up[(Len - 1) * upsample_ratio] = x[Len - 1];
    y_up[(Len - 1) * upsample_ratio] = y[Len - 1];
    count++;
}
