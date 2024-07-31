/*
Note: I have not implemented handling e-powers (e.g. -2e7).
Comparing results against standard strtod() we get the same results + end pointer data.
*/
#include <stdio.h>
#include <stdlib.h>

double my_strtod(const char* str, char** endptr);

int main() {
    char myString[] = "-3432.2a44";
    
    char *endptr1;
    double num = strtod(myString, &endptr1);
    printf("strtod output: %f\n", num);
    printf("strtod endpointer data: %c\n", *endptr1);
    
    char *endprt2;
    double num2 = my_strtod(myString, &endprt2);
    printf("my_strtod output: %f\n", num2);
    printf("my_strtod enpointer data: %c\n", *endprt2);
    return EXIT_SUCCESS;
}


double my_strtod(const char* str, char** endptr) {
    // Handle null pointers or empty string;
    if (str == 0 || *str == '\0') {
        return 0;
    }

    int sign = 1;
    double result = 0;
    double factor = 0.1;

    // Handle optional sign.
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Handle digits before decimal point.
    while (*str >= '0' && *str <= '9') {
        result = (10 * result) + (double)*str - (double)'0';
        str++;
    }

    // Handle digits after optional decimal point.
    if (*str == '.') {
        str++;
        while (*str >= '0' && *str <= '9') {
            result = result + (factor * ((double)*str - (double)'0'));
            factor /= 10;
            str++;
        }
    }
    *endptr = (char*)str;
    return sign * result;
}