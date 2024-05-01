/*
Testing example switch statement.
Observed behaviour: if a break is removed the program "falls through" to the next case, also running that one.

To run: compile and run with the desired letter as a command line arg.
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[argc+1]) {
    char arg = argv[1][0];   // Take first char on command line args
    switch (arg) {
        case 'm': 
            puts("this is a magpie");
            break;
        case 'r':
            puts("this is a raven");
            break;
        case 'j':
            puts("this is a jay");
            break;
        case 'c':
            puts("this is a chough");
            break;
        default:
            puts("this is an unknown corvid");
    }
    return EXIT_SUCCESS;
}