/*
Modern C challenge 5: Complex numerical differentiation.
This works identically to challenge 2. Just make sure you use a complex function with a known derivative (i.e. satisfy the Cauchy-Riemann equations.)
*/
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

double complex f(double complex(*func_ptr)(double complex), double complex z, double complex h);
double complex diff_csin(double complex z);

int main() {
    double complex z = 2 + 3*I;
    double complex h = 1e-6 + 0*I;

    // Compare true and numerical derivative for sin function.
    double complex true_diff = diff_csin(z);
    double complex num_diff = f(&csin, z, h);
    printf("Complex number z: %f + %fi\n", creal(z), cimag(z));
    printf("True derivative of sin(z): %f + %fi\n", creal(true_diff), cimag(true_diff));
    printf("Numerical derivative of sin(z): %f + %fi\n", creal(num_diff), cimag(num_diff));
    return EXIT_SUCCESS;
}


// Numerical differentiation, takes in a pointer to a function.
double complex f(double complex(*func_ptr)(double complex), double complex z, double complex h) {
    return ((*func_ptr)(z + h) - (*func_ptr)(z-h)) / (2*h);
}


// Analytical complex derivative for sine function.
double complex diff_csin(double complex z) {
    return ccos(z);
}


