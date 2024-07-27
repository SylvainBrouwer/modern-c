/*
Using Measure-Command {.\level1-exs50.exe} for Windows:
n = 10 -> ~7ms
n = 20 -> ~8ms
n = 40 -> ~7ms
n = 41 -> ~7ms
n = 42 -> ~7ms
n = 45 -> ~7ms
Observed results: Same execution times as fibCache, bu we use less memory.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void fib2rec(size_t n, size_t buf[2]);
size_t fib2(size_t n);


int main() {
    printf("Recursive: %zu\n", fib2(45));
    return EXIT_SUCCESS;
}


void fib2rec(size_t n, size_t buf[2]) {
    if (n > 2) {
        size_t res = buf[0] + buf[1];
        buf[1] = buf[0];
        buf[0] = res;
        fib2rec(n-1, buf);
    }
}


size_t fib2(size_t n) {
    size_t res[2] = {1, 1};
    fib2rec(n, res);
    return res[0];
}