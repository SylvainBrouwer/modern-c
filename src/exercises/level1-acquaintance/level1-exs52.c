#if !(~0 == -1)
#   error "int does not have 2's complement"
#endif

#include <stdio.h>
#include <stdlib.h>

int main() {
    puts("Some random printing in main.");
    return EXIT_SUCCESS;
}