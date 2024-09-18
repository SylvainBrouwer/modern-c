/*
You can drop both p and q and just use directly formatted strings, this seems to match the assembly closer.

Again, I've included a main function so you can run it and compare outputs, 
I recommend removing it if you just want to look at the assembly.
*/
#include <stdio.h>
#include <stdlib.h>


void fgoto(unsigned n) {
    unsigned j = 1;
    char *str = "unequal";
    const char *str_frmt = "%u: p and q are %s, *p is %u\n";
    if (n > 0) {
        AGAIN:
        printf(str_frmt, j, str, j - 1);
        str = "equal";
        ++j;
        if (j <= n) goto AGAIN;
    }
}


int main() {
    fgoto(2);
    return EXIT_SUCCESS;
}