/*
Using Measure-Command {.\level1-exs48.exe} for Windows:
n = 10 -> ~7ms
n = 20 -> ~7ms
n = 40 -> ~7ms
n = 41 -> ~7ms
n = 42 -> ~7ms
n = 45 -> ~7ms
Observed results: fairly flat performance, should be linear in n.
*/
#include <stdio.h>
#include <stdlib.h>

size_t fibCacheRec(size_t n, size_t cache[n]);
size_t fibCache(size_t n);

int main() {
    printf("%zu\n", fibCache(45));
    return EXIT_SUCCESS;
}


/* Compute Fibonacci number n with the help of a cache that may
hold previously computed values . */
size_t fibCacheRec(size_t n, size_t cache[n]) {
    if (!cache[n-1]) {
        cache[n-1] = fibCacheRec(n-1, cache) + fibCacheRec(n-2, cache);
    }
    return cache[n-1];
}


// Note: this is essentially a helper wrapper around fibCacheRec, for initializing.
size_t fibCache(size_t n) {
    if (n+1 <= 3) {
        return 1;
    }
    /* Set up a VLA to chache the values. */
    size_t cache[n];
    /* A VLA must be initialized by assignment. */
    cache[0] = 1; cache[1] = 1;
    for (size_t i = 2; i < n; i++) {
        cache[i] = 0;
    }
    /* Call the recursive function. */
    return fibCacheRec(n, cache);
}