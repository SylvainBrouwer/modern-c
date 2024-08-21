/*
Observed behaviour: We expect 70 to be the result, but we get 14 instead.
This is because the macro is simple textual replacement,
so `sum(5, 2) * 7` becomes `5 + 2 * 7` where the * operator has precedence over the + operator.
*/
#include <stdio.h>
#include <stdlib.h>

#define sum(a, b) a + b

int main() {
    int result = sum(5, 2) * 7;
    printf("%d\n", result);
    return EXIT_SUCCESS;
}
