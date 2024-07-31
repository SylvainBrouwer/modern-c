/*
Note 1: I use the C standard library implementation provided by mingw-w64 gcc,
stdout to the terminal seems to be unbuffered by default in my case.
To force the behaviour intended in this exercise set: setvbuf(stdout, NULL, _IOFBF, 1024);

Observed behaviour:
0 args -> 1. initial sentence prints 2. dots print one by one 3. final sentence prints.
1 arg -> 1. inital sentence prints 2. dots print all at once 3. (immediately after) final sentence prints
2 args -> 1. initial sentence and dots print at once 2. (immediately after) final sentence prints
*/

#include <stdio.h>

/*  delay execution with some crude code ,
    should use thrd_sleep , once we have that */
void delay(double secs) {
    double const magic = 4E8;
    unsigned long long const nano = secs * magic;
    for (unsigned long volatile count = 0; count < nano; count++) {
        /* nothing here */
    }
}

int main(int argc, char const *argv[]) {
    setvbuf(stdout, NULL, _IOFBF, 1024);
    fputs("waiting 10 seconds for you to stop me", stdout);
    if (argc < 3) {
        fflush(stdout);
    }
    delay(1);
    for (unsigned i = 0; i < 10; i++) {
        fputc('.', stdout);
        if (argc < 2) { 
            fflush(stdout);
        }
        delay(2.5);
    }
    fflush(stdout);
    fputs("\n", stdout);
    fputs("You did ignore me, so bye bye\n", stdout);
}
