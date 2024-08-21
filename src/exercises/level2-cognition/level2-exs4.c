/*
Observed behaviour: for i >= 5, it is incremented twice, as i++ is filled in for
both occurrences of `a` in the macro.
*/
#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a) < (b) ? (b) : (a))

int main() {
    int i = 0;
    while (i < 20) {
        printf("%d:", i);
        int result = max(i++, 5);
        printf("%d\n", result);
    }
    return EXIT_SUCCESS;
}