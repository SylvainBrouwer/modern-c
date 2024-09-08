/*
Modern C challenge 13: Generic derivative;

I sneakily used function pointers already in challenge 2 & 5, that code is simply copied over.
I've folded the polynomial zeros (real and complex) into one. The given function returns all roots.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <stdbool.h>

static double const newton_stop = 1e-4;
static double const max_iter = 100;
static double const eps = 1e-5;


typedef struct polynomial polynomial;
struct polynomial {
    size_t order;
    double* params;
};


double diff(double (*func_ptr)(double), double x, double h);
double complex diff_c(double complex (*func_ptr)(double complex), double complex x, double complex h);
double newtons_method(double (*func_ptr)(double), double init);
polynomial* polynomial_init(size_t N, double params[N]);
double complex polynomial_eval(polynomial* polynomial, double complex x);
void free_polynomial(polynomial* p);
double complex* polynomial_roots(polynomial* p, double complex init);

int main() {
    // Test Newtons method for real fucntions.
    double root = newtons_method(log10, 0.1);
    printf("Root for log10, using Netwons method: %.3f\n", root);

    // Create a polynomial and check it.
    size_t N = 4;
    double test_params[] = {-5, 3, -3, 1};
    polynomial* pp = polynomial_init(N, test_params);
    double complex result = polynomial_eval(pp, 7);
    printf("\nEvaluating x^3 - 3x^2 + 3x - 5, x=7:\n%.3f + %.3fI\n", creal(result), cimag(result));

    // Roots
    puts("\nFinding roots of x^3 - 3x^2 + 3x - 5:");
    double complex init = 0.4 + 0.9*I;      // Make sure this is neither a real number not a root of unity;
    double complex* roots = polynomial_roots(pp, init);
    for (size_t i = 0; i < pp->order; i++) {
        printf("Root[%zu]: %.3f + %.3fI\n", i, creal(roots[i]), cimag(roots[i]));
    }

    free_polynomial(pp);
    free(roots);
    return EXIT_SUCCESS;
}


// Numerical differentiation, takes in a pointer to a function
double diff(double (*func_ptr)(double), double x, double h) {  
    return ((*func_ptr)(x+h) - (*func_ptr)(x-h))/(2*h);
}


// Complex numerical differentiation, takes in a pointer to a function.
double complex diff_c(double complex (*func_ptr)(double complex), double complex z, double complex h) {
    return ((*func_ptr)(z + h) - (*func_ptr)(z-h)) / (2*h);
}


// Newtons method for finding a zero
double newtons_method(double (*func_ptr)(double), double init) {
    double approx = init;
    for (int iter = 0; iter < max_iter; iter++) {
        double update = func_ptr(approx) / diff(func_ptr, approx, eps);
        double approx_new = approx - update;
        if (fabs(approx - approx_new) < newton_stop) {
            return approx_new;
        }
        approx = approx_new;
    }
    return __DBL_MAX__;
}


// Initialize a polynomial with the provided parameters
polynomial* polynomial_init(size_t N, double params[N]) {
    polynomial* result = malloc(sizeof(polynomial));
    result->order = N-1;
    result->params = malloc(sizeof(size_t)*N);
    for (size_t i = 0; i < N; i++) {
        result->params[i] = params[i];
    }
    return result;
}


// Evaluate a (complex) polynomial
double complex polynomial_eval(polynomial* polynomial, double complex x) {
    double complex result = 0;
    for (size_t i = 0; i < polynomial->order+1; i++) {
        result += (polynomial->params[i] * cpow(x,i));
    }
    return result;
}


// Free a polynomial
void free_polynomial(polynomial* p) {
    if (p) {
        free(p->params);
    };
    free(p);
}


// Find all zeros of a polynomial (both real and complex)
// Uses the Durand-Kerner method
double complex* polynomial_roots(polynomial* p, double complex init) {
    double complex* roots = malloc(sizeof(double complex)*p->order);
    for (size_t i = 0; i < p->order; i++) {
        roots[i] = cpow(init, i);
    }
    for (size_t iter = 0; iter < max_iter; iter++) {
        bool stop = true;
        for (size_t r1 = 0; r1 < p->order; r1++) {
            double complex numerator = polynomial_eval(p, roots[r1]);
            double complex denominator = 1;
            for (size_t r2 = 0; r2 < p->order; r2++) {
                if (r1 != r2) {
                    denominator *= (roots[r1] - roots[r2]);
                }
            }
            double complex update = numerator / denominator;
            roots[r1] -= update;
            if (cabs(update) > newton_stop) {
               stop = false;
            }
        }
        if (stop) {
            return roots;
        }
    }
    return roots;
}