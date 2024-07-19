/*
Type is checked by the print formatters.
For my system, the max lengths of U and LU were identical: 2^{32}-1.
Max size for LLU was 2^{64}-1.
This should be the same for most modern systems.
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("%u\n", -1U);
    printf("%lu\n", -1LU);
    printf("%llu\n", -1LLU);
    return EXIT_SUCCESS;
}