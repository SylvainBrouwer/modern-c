/*
On top of the asked behaviour, I have added a check that makes sure that the provided buffer size is large enough.
Note: I've included all rat-related functions from exercise 8, even if they are not strictly necessary for this exercise.
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
rat* rat_init(rat* rp, long long num, unsigned long long denom);
char const* rat_print(size_t len, char tmp[len], rat const* x);


int main() {
    rat r;
    rat_init(&r, 100000, 20000000);
    size_t buffsize = 50;
    char buffer[buffsize];
    if (rat_print(buffsize, buffer, &r)) {
        printf("%s\n", buffer);
    }
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


rat* rat_init(rat* rp, long long num, unsigned long long denom) {
    if (rp) {
        *rp = rat_get(num, denom);
    }
    return rp;
}


char const* rat_print(size_t len, char tmp[len], rat const* x) {
    if (len == 0 || tmp == 0 || x == 0) {
        fprintf(stderr, "Malformed input.");
        return 0;
    }
    int req_buffer_length = snprintf(0, 0, "+%lld/%llu", x->num, x->denom);
    if (len < req_buffer_length) {
        fprintf(stderr, "Provided buffer is too small.");
        return 0;
    }
    char sign;
    sign = x->sign == true ? '-' :  '+';
    sprintf(tmp, "%c%lld/%llu", sign, x->num, x->denom);
    return tmp;
}