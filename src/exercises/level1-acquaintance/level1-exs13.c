/*
Positive singed values include 0, therefore max(long long) = abs(min(long long)) - 1.
Any literal 'x' such that min(long long) = -x would thus have to be x = max(long long) + 1.
However this is not possible as this would result in an overflow error. (try it out by adding 1 to LLONG_MAX below)
*/
#include <stdio.h>
#include <stdlib.h>


int main(){
    printf("%llu\n", LLONG_MAX);
    printf("%llu\n", LLONG_MIN);
    return EXIT_SUCCESS;
}