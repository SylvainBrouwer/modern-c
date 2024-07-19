/*
Q: Prove that for unsigned arithmetic, A + ~A is the maximum value.

A:
Note that ~A corresponds to all bits not set by A, so A + ~A will have all bits set, which by definition is the max value for unsigned values.
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    unsigned long a = 23243243; // Pick some value 
    unsigned long b = ~a;
    printf("max value: %lu\n a + ~a: %lu", ULONG_MAX, a+b);
    return EXIT_SUCCESS;
}