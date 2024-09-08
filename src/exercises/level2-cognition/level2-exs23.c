/*
Observed behaviour: 
The pointer adress printed with the %p format specifier exactly matches the hex representations of the bytes.
*/
#include <stdio.h>
#include <stdlib.h>

typedef union pointerInspect pointerInspect;

union pointerInspect {
    double* dp;
    unsigned char bytes[sizeof(double*)];
};

int main() {
    double a = 2.0;
    pointerInspect test = {.dp = &a};
    printf("Pointer: %p\n", test.dp);
    for (size_t i = 0; i < sizeof(test.dp); i++) {
        printf("byte [%zu]: 0x%.02hhX\n", i, test.bytes[i]);
    }
    return EXIT_SUCCESS;
}