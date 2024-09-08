/*
Observed behaviour: The adresses are consecutive, differing only by sizeof(double*).
*/
#include <stdio.h>
#include <stdlib.h>

typedef union pointerInspect pointerInspect;

union pointerInspect {
    double* dp;
    unsigned char bytes[sizeof(double*)];
};

int main() {
    double a[] = {2.0, 4.0};
    pointerInspect test1 = {.dp = &a[0]};
    pointerInspect test2 = {.dp = &a[1]};
    for (size_t i = 0; i < sizeof(double*); i++) {
        printf("byte [%zu]: 0th element: 0x%.02hhX, 1st element: 0x%.02hhX\n", i, test1.bytes[i], test2.bytes[i]);
    }
    return EXIT_SUCCESS;
}