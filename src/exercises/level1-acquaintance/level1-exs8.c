/*
Implemented to 24-hr clock computations suggested.
Nothing too exciting.
*/
#include <stdio.h>

int main() {
    int comp1 = (10 + 3) % 24;
    int comp2 = (20 + 8) % 24;
    printf("Result 1: %d\nResult 2: %d\n", comp1, comp2);
    return 0;
}