/*
Use memchr and memcmp to implement a bounds-checking version of strcmp.
If one of two inputs does not have a terminating symbol, we return -1.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strcmp_bounded(char s1[], char s2[], size_t length);

int main() {
    char s1[] = "This";
    char s2[] = "That";
    char s3[] = "Thi";
    char s4[] = {'T', 'h', 'i', 's'};
    printf("s1 -s1: %d\n", strcmp_bounded(s1, s1, sizeof(s1)));
    printf("s1 -s2: %d\n", strcmp_bounded(s1, s2, sizeof(s1)));
    printf("s1 -s2: %d\n", strcmp_bounded(s2, s1, sizeof(s1)));
    printf("s1 -s3: %d\n", strcmp_bounded(s1, s3, sizeof(s1)));
    printf("s3 -s1: %d\n", strcmp_bounded(s3, s1, sizeof(s1)));
    printf("s1 -s4: %d\n", strcmp_bounded(s1, s4, sizeof(s1)));
    
    return EXIT_SUCCESS;
}


int strcmp_bounded(char s1[], char s2[], size_t length) {
    char* terminating1 = memchr(s1, '\0', length);
    char* terminating2 = memchr(s2, '\0', length);
    if (terminating1 && terminating2) {
        size_t diff1 = (size_t) abs((int) (terminating1 - s1));
        size_t diff2 = (size_t) abs((int) (terminating2 - s2));
        size_t min_diff;
        if (diff1 < diff2) {
            min_diff = diff1;
        } else {
            min_diff = diff2;
        }
        int result = memcmp(s1, s2, min_diff);
        if (result) {
            return result;
        }
        return diff1 - diff2;
    }
    return -1;
}
