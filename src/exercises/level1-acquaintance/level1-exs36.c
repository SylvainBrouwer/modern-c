/*
Observed behaviour: Both result in 0.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    long double a = 1.0E-13 + 1.0E-13;
    long double b = (1.0E-13 + (1.0E-13 + 1.0)) - 1.0;
    printf("%Lf\n", a);
    printf("%Lf\n", b);
    return EXIT_SUCCESS;
}