/*
Modern C challenge 9: factorization
I do not check that the input numbers are well formed / all integers < SIZE_MAX.
So make sure your command line arguments are correct.
*/
#include <stdio.h>
#include <stdlib.h>

void primeFactors(size_t n);
size_t smallestPrimeFactor(size_t n);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "No numbers were passed!\n");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i ++) {
        char *endptr;
        size_t num = (size_t) strtoull(argv[i], &endptr, 10);
        // Theres a bunch or error checking you should probably do here but I'm not going to bother.
        primeFactors(num);
    }
    return EXIT_SUCCESS;
}


// Print prime factorization for n
void primeFactors(size_t n) {
    printf("%zu:", n);
    size_t rem = n;
    do {
        size_t factor = smallestPrimeFactor(rem);
        printf(" %zu", factor);
        rem /= factor;
    } while (rem > 1);
    printf("\n");
}


// Find smallest prime factor for n
size_t smallestPrimeFactor(size_t n) {
    if (n%2 == 0) {
        return 2;
    }
    for (size_t i = 3; i*i <= n; i+=2) {
        if (n%i == 0) {
            return i;
        }
    }
    return n;
}