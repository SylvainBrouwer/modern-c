/*
Observed behaviour: -1
Note that this makes sense as INT_MAX = 2^p - 1 while INT_MIN = -2^p due to positive values including 0.
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("%d", INT_MIN+INT_MAX);
    return EXIT_SUCCESS;
}