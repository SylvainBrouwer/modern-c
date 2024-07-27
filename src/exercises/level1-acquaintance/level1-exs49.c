/*
You can choose between the recursive and iterative variant using the `bool iter` parameter in fib2; 
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void fib2rec(size_t n, size_t buf[2]);
void fib2iter(size_t n, size_t buf[2]);
size_t fib2(size_t n, bool iter);


int main() {
    printf("Recursive: %zu\n", fib2(40, false));
    printf("Iterative: %zu\n", fib2(40, true));
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


void fib2iter(size_t n, size_t buf[2]) {
    if (n > 2) {
        for (size_t i = 2; i < n; i++) {
            size_t res = buf[0] + buf[1];
            buf[1] = buf[0];
            buf[0] = res;
        }
    }

}

size_t fib2(size_t n, bool iter) {
    size_t res[2] = {1, 1};
    if (iter) {
        fib2iter(n, res);
    } else {
        fib2rec(n, res);
    }
    return res[0];
}