/*
Note: Again, I've included all rat-related functions from exercise 8, 14 & 15, even if they are not strictly necessary for this exercise.
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
rat* rat_normalize(rat* rp);
char const* rat_print_normalized(size_t len, char tmp[len], rat* x);
rat* rat_sumup(rat* rp, rat y);
rat* rat_dotproduct(rat* rp, size_t n, rat const A[n], rat const B[n]);


int main() {
    // Set up two arrays of rats
    size_t size = 4;
    rat A[size];
    rat B[size];
    for (size_t i = 0; i < size; i++) {
        A[i] = rat_get(1, 2*(i+1));
        B[i] = rat_get(2, 3*(i+1));
    }

    // Dot product + print
    rat r;
    rat_dotproduct(&r, size, A, B);
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


rat rat_get_extended(rat x, size_t f) {
    x.num *= f;
    x.denom *= f;
    return x;
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


rat* rat_normalize(rat* rp) {
    if (rp) {
        *rp = rat_get_normal(*rp);
    }
    return rp;
}


char const* rat_print_normalized(size_t len, char tmp[len], rat* x) {
    rat const* rp_norm = rat_normalize(x);
    return rat_print(len, tmp, rp_norm);
}


rat* rat_extend(rat* rp, size_t f) {
    if (rp) {
        *rp = rat_get_extended(*rp, f);
    }
    return rp;
}


rat* rat_rma(rat* rp, rat x, rat y) {
    return rat_sumup(rp, rat_get_prod(x, y));
}


rat* rat_sumup(rat* rp, rat y) {
    size_t c = gcd(rp->denom, y.denom);
    size_t ax = y.denom/c;
    size_t bx = rp->denom/c;
    rat_extend(rp, ax);
    y = rat_get_extended(y, bx);
    assert(rp->denom == y.denom);

    if(rp->sign == y.sign) {
        rp->num += y.num;
    } else if (rp->num > y.num) {
        rp->num -= y.num;
    } else {
        rp->num = y.num - rp->num;
        rp->sign = !rp->sign;
    }
    return rat_normalize(rp);
}


rat* rat_dotproduct(rat* rp, size_t n, rat const A[n], rat const B[n]) {
    rp = rat_init(rp, 0, 1);
    for(size_t i = 0; i < n; i++) {
        rat_rma(rp, A[i], B[i]);
    }
    return rp;
}