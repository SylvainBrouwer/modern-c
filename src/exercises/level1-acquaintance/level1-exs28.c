/*
We can check lost information / bits by shifting a number right and then back left again.
Compare this value against the remainder a % (1UL << n).
Observed behaviour: The values are the same.
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    unsigned long a = 243458934; // Just pick some large number
    int n  = 3;
    unsigned long b = a >> n;
    unsigned long c = b << n;
    unsigned long remainder = a % (1UL << n);
    
    printf("lost information: %lu, remainder: %lu", a-c, remainder);

    return EXIT_SUCCESS;
}