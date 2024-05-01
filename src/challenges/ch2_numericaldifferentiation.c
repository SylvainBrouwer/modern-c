/*
Modern C challenge 2: numerical differentiation.
Note: I have not given an explicit double F(double x),
f takes in a function pointer allowing us to pass arbitrary functions.
(As long as they take a single double argument and returns a double)
*/
#include <stdio.h>
#include <math.h>

double f(double (*func_ptr)(double), double x, double h);
double diff_sqrt(double x);
double diff_sin(double x);


int main() {
    double x[] = {0, 1, 2, 3, 4, 5, 6, 7};
    double h = 0.001;

    // Numerical differentiation + comparison for sqrt
    for (int i =0; i<8; i++){
        printf("F(%f) = sqrt(%f) = %f | ", x[i], x[i], sqrt(x[i]));
        printf("calculated f(%f): %f | ", x[i], f(&sqrt, x[i], h));
        printf("true f(%f): %f\n", x[i], diff_sqrt(x[i]));
    }

    printf("\n\n");
    // Numerical differentiation + comparison for sin
    for (int i =0; i<8; i++){
        printf("F(%f) = sqrt(%f) = %f | ", x[i], x[i], sin(x[i]));
        printf("calculated f(%f): %f | ", x[i], f(&sin, x[i], h));
        printf("true f(%f): %f\n", x[i], diff_sin(x[i]));
    }
    return 0;
}

// Numerical differentiation, takes in a pointer to a function
double f(double (*func_ptr)(double), double x, double h) {  
    return ((*func_ptr)(x+h) - (*func_ptr)(x-h))/(2*h);
}

// Analytical derivative of sqrt
double diff_sqrt(double x) {
    return 0.5*(1/sqrt(x));
}

// Analytical derivative of sin
double diff_sin(double x) {
    return cos(x);
}