/*
Resizing has been implemented.
As testing the various cases requires specific configurations of the buffer, I manually create them instead up using `circular_new`.
Note: printBuff is valid / has defined behaviour, as I initialize unused buffer slots to 0.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct circular circular;
struct circular {
    size_t start;   // Position of element 0
    size_t len;     // Number of elements stored
    size_t max_len; // Maximum capacity
    double* tab;    // Array holding data
};

circular* circular_append(circular* c, double value);
double circular_pop(circular* c);
double* circular_element(circular* c, size_t pos);
circular* circular_init(circular* c, size_t max_len);
void circular_destroy(circular* c);
circular* circular_new(size_t len);
void circular_delete(circular* c);
size_t circular_getlength(circular* c);
static size_t circular_getpos(circular* c, size_t pos);
circular* circular_resize(circular* c, size_t nlen);
void printBuff(double* buff, size_t len);


static size_t buffsize = 6;

int main() {
    puts("Situation 1: Extend + the lower part finds enough space inside the part that was added.");
    double arr1[] = {3, 4, 0, 0, 1, 2};
    double* tab1 = malloc(buffsize*sizeof(double));
    for (size_t i = 0; i < buffsize; i++) {
        *(tab1+i) = arr1[i];
    }
    circular circle1 = {
        .start = 4,
        .len = 4,
        .max_len = buffsize,
        .tab = tab1,
    };
    circular* c = &circle1;
    puts("Before:");
    printBuff(c->tab, c->max_len);
    printf("start: %zu, len: %zu, max_len: %zu\n", c->start, circular_getlength(c), c->max_len);
    circular_resize(c, 8);
    puts("After:");
    printBuff(c->tab, c->max_len);
    printf("start: %zu, len: %zu, max_len: %zu\n", c->start, circular_getlength(c), c->max_len);
    free(c->tab);

    puts("\nSituation 2: Extend + the lower part doesn’t fit into the newly allocated part.");
    double arr2[] = {3, 4, 0, 0, 1, 2};
    double* tab2 = malloc(buffsize*sizeof(double));
    for (size_t i = 0; i < buffsize; i++) {
        *(tab2+i) = arr2[i];
    }
    circular circle2 = {
        .start = 4,
        .len = 4,
        .max_len = buffsize,
        .tab = tab2,
    };
    c = &circle2;
    puts("Before:");
    printBuff(c->tab, c->max_len);
    printf("start: %zu, len: %zu, max_len: %zu\n", c->start, circular_getlength(c), c->max_len);
    circular_resize(c, 7);
    puts("After:");
    printBuff(c->tab, c->max_len);   
    printf("start: %zu, len: %zu, max_len: %zu\n", c->start, circular_getlength(c), c->max_len);
    free(c->tab);

    puts("\nSituation 3: Shrink + everything is consecutive.");
    double arr3[] = {0, 0, 1, 2, 3, 4};
    double* tab3 = malloc(buffsize*sizeof(double));
    for (size_t i = 0; i < buffsize; i++) {
        *(tab3+i) = arr3[i];
    }
    circular circle3 = {
        .start = 2,
        .len = 4,
        .max_len = buffsize,
        .tab = tab3,
    };
    c = &circle3;
    puts("Before:");
    printBuff(c->tab, c->max_len);
    printf("start: %zu, len: %zu, max_len: %zu\n", c->start, circular_getlength(c), c->max_len);
    circular_resize(c, 5);
    puts("After:");
    printBuff(c->tab, c->max_len);
    printf("start: %zu, len: %zu, max_len: %zu\n", c->start, circular_getlength(c), c->max_len);
    free(c->tab);

    puts("\nSituation 4: Shrink + wrap around.");
    double arr4[] = {3, 4, 0, 0, 1, 2};
    double* tab4 = malloc(buffsize*sizeof(double));
    for (size_t i = 0; i < buffsize; i++) {
        *(tab4+i) = arr4[i];
    }
    circular circle4 = {
        .start = 4,
        .len = 4,
        .max_len = buffsize,
        .tab = tab4,
    };
    c = &circle4;
    puts("Before:");
    printBuff(c->tab, c->max_len);
    printf("start: %zu, len: %zu, max_len: %zu\n", c->start, circular_getlength(c), c->max_len);
    circular_resize(c, 4);
    puts("After:");
    printBuff(c->tab, c->max_len);
    printf("start: %zu, len: %zu, max_len: %zu\n", c->start, circular_getlength(c), c->max_len);
    free(c->tab);
    return EXIT_SUCCESS;
}


/*
Initialize a circular buffer c with maximally `max_len` elements.
*/
circular* circular_init(circular* c, size_t max_len) {
    if (c) {
        if (max_len) {
            *c = (circular) {
                .max_len = max_len,
                .tab = malloc(max_len*sizeof(double))
            };
            if (!c->tab) {
                c->max_len = 0;
            } 
        } else {
            *c = (circular){0};
        }
    }
    return c;
}


/*
Destroy a circular buffer c.
*/
void circular_destroy(circular* c) {
    if (c) {
        free(c->tab);
        circular_init(c, 0);
    }
}


static size_t circular_getpos(circular* c, size_t pos) {
    pos += c->start;
    pos %= c->max_len;
    return pos;
}


/*
Return a pointer to position `pos` in buffer `c`.
**Returns**: a pointer to the `pos` element of the buffer, 0 otherwise. 
*/
double* circular_element(circular* c, size_t pos) {
    double* ret = 0;
    if (c) {
        if (pos < c->max_len) {
            pos = circular_getpos(c, pos);
            ret = c->tab + pos;
        }
    }
    return ret;
}


/*
Allocate and initialize a circular buffer with maximally `len` element.
*/
circular* circular_new(size_t len) {
    circular* c = malloc(sizeof(circular));
    if (c) {
        c->len = 0;
        c->start = 0;
        c = circular_init(c, len);
    }
    return c;
}


/*
Delete a circular buffer `c`.
*/
void circular_delete(circular* c) {
    if (c) {
        circular_destroy(c);
        free(c);
    }
}


/*
Return the number of elements stored.
*/
size_t circular_getlength(circular* c) {
    if (c) {
        return c->len;
    }
    return 0;
}


/*
Append a new element with value.
**Returns:** `c` if the new element could be appended, 0 otherwise.
*/
circular* circular_append(circular* c, double value) {
    if (c) {
        size_t next_pos = circular_getlength(c);
        double* elem = circular_element(c, next_pos);
        if (elem) {
            *elem = value;
            c->len += 1;
            return c;
        }
    }
    return 0;
}


/*
Remove the oldest element from `c` and return it's value.
**Returns:** the removed element if it exists, 0.0 otherwise.
*/
double circular_pop(circular* c) {
    double ret = 0.0;
    if (c && circular_getlength(c)) {
        double* elem = circular_element(c, 0);
        if (elem) {
            c->start++;
            c->start %= c->max_len;
            c->len--;
            return *elem;
        }
    }
    return ret;
}


/*
Resize to capacity `max_len`.
*/
circular* circular_resize(circular* c, size_t nlen) {
    if (c) {
        size_t len = c->len;
        if (len > nlen) {
            return 0;
        }
        size_t olen = c->max_len;
        if (nlen != olen) {
            size_t ostart = circular_getpos(c, 0);
            size_t nstart = ostart;
            double* otab = c->tab;
            double* ntab;
            if (nlen > olen) {
                ntab = realloc(c->tab, sizeof(double[nlen]));
                if (!ntab) return 0;
                if (ostart+len > olen) {
                    size_t ulen = olen - ostart;
                    size_t llen = len-ulen;
                    if (llen <= (nlen - olen)) {
                        memcpy(ntab+olen, ntab, llen*sizeof(double));
                    } else {
                        nstart = nlen - ulen;
                        memmove(ntab+nstart, ntab+ostart, ulen*sizeof(double));
                    }
                }
            } else {
                if (ostart+len > olen) {
                    size_t ulen = olen - ostart;
                    size_t sizediff = olen - nlen;
                    nstart = ostart - sizediff;
                    memmove(otab+nstart, otab+ostart, ulen*sizeof(double));
                } else {
                    nstart = 0;
                    memmove(otab, otab+ostart, len*sizeof(double));
                }
                ntab = realloc(c->tab, sizeof(double[nlen]));
                if(!ntab) return 0;
            }
            *c = (circular) {
                .max_len = nlen,
                .start = nstart,
                .len = len,
                .tab = ntab,             
            };
        }

    }
    return c;
}


// Some utility for visualizing the buffer.
void printBuff(double* buff, size_t len) {
    printf("Array: ");
    for (size_t i = 0; i < len; i++) {
        printf("%.2f ", *(buff+i));
    }
    printf("\n");
}