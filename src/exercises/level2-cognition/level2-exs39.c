/*
I'm not entirely sure about this one.
Start at j=1 and point p to j. Just check for q, instead of q==p.

I've included a main function so you can run it and compare outputs, 
I recommend removing it if you just want to look at the assembly.
*/
#include <stdio.h>


void fgoto(unsigned n) {
    unsigned j = 1;
    unsigned *p = &((unsigned){0,});
    unsigned *q = 0;
    if (n > 0) {
        AGAIN:
        printf("%u: p and q are %s, *p is %u\n",
            j,
            q ? "equal" : "unequal",
            *p);
        q = p;
        *p = (unsigned){j,};
        ++j;
        if (j <= n) goto AGAIN ;
    }
}


int main() {
    fgoto(2);
    return 0;
}