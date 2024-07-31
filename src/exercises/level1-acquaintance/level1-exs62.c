#include <stdio.h>
#include <stdlib.h>

size_t find_prefix(char const s[static 1], size_t i, char const p[]);

int main() {
    printf("0xFFFF (hex): %zu\n", find_prefix("0xFFFF", 0, "0x"));
    printf("0347 (octal): %zu\n", find_prefix("0347", 0, "0x"));
    printf("223 (decimal): %zu\n", find_prefix("223", 0, "0x"));
    return EXIT_SUCCESS;
}


size_t find_prefix(char const s[static 1], size_t i, char const prefix[]) {
    size_t j = 0;
    while (prefix[j] != '\0') {
        if (!(s[i+j] == prefix[j])) {
            return j;
        }
        j++;
    }
    return j;
}