/*
Printing eps1m01.
Observed behaviour: 0x1P-1 is a hexadecimal float, value after P indicates the power. (e is a value in hex thus p is used)
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    static double const eps1m01 = 1.0 - 0x1P-1;     // Change this value and observe the different outputs.
    printf("%f\n", eps1m01);
    return EXIT_SUCCESS;
}