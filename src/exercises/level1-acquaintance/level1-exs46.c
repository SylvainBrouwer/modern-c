/*
Using Measure-Command {.\level1-exs46.exe} for Windows:
n = 10 -> ~8ms
n = 20 -> ~8ms
n = 40 -> ~360ms
n = 41 -> ~570ms
n = 42 -> ~900ms
n = 45 -> ~3.8s
Observed behaviour: Fairly flat performance to a certain point, then it explodes (exponential) with the size of n.
*/
#include <stdio.h>
#include <stdlib.h>


size_t fib(size_t n);


int main() {
    printf("%zu\n", fib(45));
    return EXIT_SUCCESS;
}


size_t fib(size_t n) {
    if (n < 3) {
        return 1;
    } else {
        return fib(n-1) + fib(n-2);
    }
}