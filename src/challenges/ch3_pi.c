/*
Modern C challenge 3: decimal places of pi.
I've reduced this to calculating the Leibniz approximation of pi.
Precision can be tuned by changing the number of terms in the approximation.
*/
#include <stdio.h>
#include <stdlib.h>

double leibniz(int terms);


int main() {
    int n_terms[] = {10, 100, 1000, 10000, 100000, 1000000};
    size_t length = sizeof(n_terms) / sizeof(n_terms[0]);
    for (int i = 0; i<length; i++) {
        printf("Leibniz approximation, %d terms: %f\n", n_terms[i], leibniz(n_terms[i]));
    }
    return 0;
}


// Leibniz approximation of pi.
double leibniz(int terms) {
    double quarter_pi = 0;
    for (int i = 0; i < terms; i++) {
        double term = (double) 1/(2*i + 1);
        if (i%2) {
            quarter_pi -= term;
        } else {
            quarter_pi += term;
        }
    }
    return 4*quarter_pi;
}