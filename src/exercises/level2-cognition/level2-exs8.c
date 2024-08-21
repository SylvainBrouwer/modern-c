/*
To solve this exercise, normalize the two input `rat` structs before multiplying `.num` and `.denom`
Note: All code except `rat_get_prod` has been taken from the book.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// Define rat struct
typedef struct rat {
    bool sign;
    size_t num;
    size_t denom;
} rat;

// Function declarations
size_t gcd2(size_t a, size_t b);
size_t gcd(size_t a, size_t b);
rat rat_get(long long num, unsigned long long denom);
rat rat_get_normal(rat x);
rat rat_get_prod(rat x, rat y);


int main() {
    rat a = rat_get(15, 20);
    rat b = rat_get(1, 2);
    rat c = rat_get_prod(a, b);
    printf("num: %zu\n", c.num);
    printf("denom: %zu\n", c.denom);
    return EXIT_SUCCESS;
}


size_t gcd2(size_t a, size_t b) {
    assert(a <= b);
    if (!a) return b;
    size_t rem = b % a;
    return gcd2(rem, a);
}


size_t gcd(size_t a, size_t b) {
    assert(a);
    assert(b);
    if(a < b) {
        return gcd2(a, b);
    } else {
        return gcd2(b, a);
    }
}


rat rat_get(long long num, unsigned long long denom) {
    rat ret = {
        .sign = (num < 0),
        .num = (num < 0) ? -num : num,
        .denom = denom
    };
    return ret;
}


rat rat_get_normal(rat x) {
    size_t c= gcd(x.num, x.denom);
    x.num /= c;
    x.denom /= c;
    return x;
}


rat rat_get_prod(rat x, rat y) {
    x = rat_get_normal(x);
    y = rat_get_normal(y);
    rat ret = {
        .sign = (x.sign != y.sign),
        .num = x.num * y.num,
        .denom = x.denom * y.denom
    };
    return ret;
}
