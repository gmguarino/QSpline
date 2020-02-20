#ifndef QSpline
#define QSpline

struct SplineCoeff
{
    int len;
    double *a;
    double *b;
    double *c;
    double *d;
};

void cubic_spline_coefficients(double x[/*Len*/], double y[/*Len*/], struct SplineCoeff *coeff, int Len);

double spline_interpolation(double x[/*Len*/], double y[/*Len*/], double x_up[/*(Len - 1) * upsample_ratio + 1*/], 
                          double y_up[/*(Len - 1) * upsample_ratio + 1*/], int Len, int upsample_ratio);

#endif
