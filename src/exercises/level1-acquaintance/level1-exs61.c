/*
We can simply use `tolower` instead of `toupper`, as we have asserted that lowercase characters are ordered and contiguous.
*/ 
#include <ctype.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
unsigned hexatridecimal(int a);

/* Supposes that lowercase characters are ordered and contiguous.*/
static_assert('z'-'a' == 25, "lowercase alphabetic characters not contiguous");

int main() {
    printf("6: %u\n", hexatridecimal('6'));
    printf("c: %u\n", hexatridecimal('c'));
    printf("G: %u\n", hexatridecimal('G'));
    printf("$: %u\n", hexatridecimal('$'));
    return EXIT_SUCCESS;
}

/* Converts an alphanumeric digit to an unsigned */
/* '0' ... '9' => 0 .. 9u */
/* 'A' ... 'Z' => 10 .. 35u */
/* 'a' ... 'z' => 10 .. 35u */
/* Other values => Greater */
unsigned hexatridecimal(int a) {
    if (isdigit(a)) {
        /*  This is guaranteed to work : decimal digits
            are consecutive , and isdigit is not
            locale dependent . */
        return a - '0';
    } else {
        /* Leaves a unchanges if it is not lowercase */
        a = tolower(a);
        return ((islower(a))) ? 10 + a - 'a' : -1;
    }
}