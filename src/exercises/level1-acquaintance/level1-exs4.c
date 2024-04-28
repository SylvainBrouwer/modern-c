/*
Heron approximation for multiplicative inverse.
Added printf statements for intermediate values of x.
Observed behaviour:
Fist loop approximates using powers of 2, takes long to converge to sufficient accuracy (hence a band of 0.5 - 1.5 is allowed).
Second loop approximates using Heron approximation, converges much faster at better accuracy.

To run: compile and then pass command line args.
*/
#include <stdlib.h>
#include <stdio.h>

/* lower and upper iteration limits centered around 1.0 */
static double const eps1m01 = 1.0 - 0x1P-01;
static double const eps1p01 = 1.0 + 0x1P-01;
static double const eps1m24 = 1.0 - 0x1P-24;
static double const eps1p24 = 1.0 + 0x1P-24;

int main(int argc, char* argv[argc+1]) {
    for (int i = 1; i < argc; i++) {            // process args
        double const a = strtod(argv[i], 0);    // arg -> double
        double x = 1.0;
        for (;;) {                              // by powers of 2
            printf("Loop 1: x = %f\n", x);
            double prod = a*x;
            if (prod < eps1m01) {
                x *= 2.0;
            } else if (eps1p01 < prod) {
                x *= 0.5;
            } else {
                break;
            }
        }
        for (;;) {                              // Heron approximation
            printf("Loop 2: x = %f\n", x);
            double prod = a*x;
            if ((prod < eps1m24) || (eps1p24 < prod)) {
                x *= (2.0-prod);
            } else {
                break;
            }
        }
        printf(" heron : a =%.5e ,\tx =%.5e ,\ta*x =%.12f\n", a, x, a*x);
    }
    return EXIT_SUCCESS;
}