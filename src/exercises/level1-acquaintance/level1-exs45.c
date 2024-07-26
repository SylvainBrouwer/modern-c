/*
This exercise is pretty trivial, leaf calls are the calls that return 1, i.e. those where n=1 or n=2;
Since all calls to fib are broken up to these base cases, and each base case adds 1 to the output, 
the number of leaf calls is necessarily equal to the fibbonaci number. 
*/
#include <stdio.h>
#include <stdlib.h>

static size_t leafcounter = 0;

size_t fib(size_t n);

int main() {
    size_t fib14 = fib(14);
    printf("fib(14) = %zu\n", fib14);
    printf("Leaf invocations: %zu\n", leafcounter);
    return EXIT_SUCCESS;
}


size_t fib(size_t n) {
    if (n < 3) {
        // Leaf calls go here.
        leafcounter += 1;
        return 1;
    } else {
        return fib(n-1) + fib(n-2);
    }
}