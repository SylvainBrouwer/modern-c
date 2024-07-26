/*
I think I covered all edge cases (i.e. when seconds diff is 0).
Try out different values in t1 and t2.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct timespec timespecdiff(struct timespec t1, struct timespec t2);

int main() {
    struct timespec t1 = {
        .tv_sec = 1,
        .tv_nsec = 232
    };

    struct timespec t2 = {
        .tv_sec = 1,
        .tv_nsec = 300
    };
    struct timespec diff = timespecdiff(t1, t2);
    printf("Diff sec: %lld\n", diff.tv_sec);
    printf("Diff nsec: %ld\n", diff.tv_nsec);
    return EXIT_SUCCESS;
}


struct timespec timespecdiff(struct timespec t1, struct timespec t2) {
    struct timespec diff;
    if (t1.tv_sec > t2.tv_sec) {
        diff.tv_sec = t1.tv_sec - t2.tv_sec;
        diff.tv_nsec = t1.tv_nsec - t2.tv_nsec;
    } else {
        diff.tv_sec = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    if (diff.tv_nsec < 0) {
        // Note: seconds should be >= 0, nsec should be [0, 999999999]
        if (diff.tv_sec == 0) {
            diff.tv_nsec = labs(diff.tv_nsec);
        } else {
            diff.tv_nsec += 1000000000L;
            diff.tv_sec -= 1;
        }
    }
    return diff;
}