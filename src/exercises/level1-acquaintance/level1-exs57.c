/*
Again, there might be a more elegant way to avoid code duplication, but this works.
*/
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

enum {buf_max = 32,};

int main(int argc, char const *argv[]) {
    int ret = EXIT_FAILURE;
    char buffer[buf_max] = {0};
    int arg_start = 1;
    bool linenum = false;
    if (argc > 1 && !strcmp(argv[arg_start], "-n")) {
        linenum = true;
        arg_start++;
    }
    if (argc > arg_start) {
        for (int i = arg_start; i < argc; i++) {            // Processes args
            FILE* instream = fopen(argv[i], "r");           // as filenames
            if (instream) {
                size_t j = 0;
                while(fgets(buffer, buf_max, instream)) {
                    if (linenum) fprintf(stdout, "%zu:", j);
                    fputs(buffer, stdout);
                    j++;
                }
                fclose(instream);
                ret = EXIT_SUCCESS;
            } else {
                /* Provides some error diagnostic. */
                fprintf(stderr, "Could not open %s: ", argv[i]);
                perror(0);
                errno = 0;                                  // Resets the error code
            }
        }
    } else {
        fputs("No files supplied, using terminal.\nEnter Ctrl+Z (Windows) / Ctrl+D (Unix) for EOF.\n", stdout);
        size_t j = 0;
        while(fgets(buffer, buf_max, stdin)) {
                if (linenum) fprintf(stdout, "%zu:", j);
                fputs(buffer, stdout);
                j++;
            }
        ret = EXIT_SUCCESS;
    }
    return ret;
}
