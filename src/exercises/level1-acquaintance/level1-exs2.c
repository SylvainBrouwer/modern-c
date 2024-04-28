/*
When decrementing a variable of type size_t set to 0, we observe that it wraps around to SIZE_MAX.
This is expected behaviour for a signed value.
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t test = 0;
    printf("test - 1: %zu\n", test-1);
    printf("SIZE_MAX: %zu\n", SIZE_MAX);
}