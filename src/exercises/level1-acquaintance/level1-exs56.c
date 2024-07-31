/*
Note: The way is set it up, you need to pass EOF manually in the terminal, this is Ctrl+Z (Windows) or Ctrl+D (Unix).

There might be a more elegant way to avoid code duplication, but this works.
*/
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

enum {buf_max = 32,};

int main(int argc, char const *argv[]) {
    int ret = EXIT_FAILURE;
    char buffer[buf_max] = {0};
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {            // Processes args
            FILE* instream = fopen(argv[i], "r");   // as filenamesd
            if (instream) {
                while(fgets(buffer, buf_max, instream)) {
                    fputs(buffer, stdout);
                }
                fclose(instream);
                ret = EXIT_SUCCESS;
            } else {
                /* Provides some error diagnostic. */
                fprintf(stderr, "Could not open %s: ", argv[i]);
                perror(0);
                errno = 0;                          // Resets the error code
            }
        }
    } else {
        fputs("No files supplied, using terminal.\nEnter Ctrl+Z (Windows) / Ctrl+D (Unix) for EOF.\n", stdout);
        while(fgets(buffer, buf_max, stdin)) {
                fputs(buffer, stdout);
            }
        ret = EXIT_SUCCESS;
    }
    return ret;
}
