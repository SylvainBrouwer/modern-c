/*
Observed behaviour: cycles through values as intended.
*/
#include <stdio.h>
#include <stdlib.h>

void cycle(double* p1, double* p2, double* p3);

int main() {
    double d1 = 1.5;
    double d2 = 50;
    double d3 = 100;
    for (int i = 0; i < 10; i++) {
        printf("d1: %.1f, d2: %.1f, d3: %.1f\n", d1, d2, d3);
        puts("Cycling...");
        cycle(&d1, &d2, &d3);
    }
    return EXIT_SUCCESS;
}


void cycle(double* p1, double* p2, double* p3) {
    double temp = *p3;
    *p3 = *p2;
    *p2 = *p1;
    *p1 = temp;
}