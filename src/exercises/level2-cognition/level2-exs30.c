/*
All functions except `circular_resize` have been implemented.
*/
#include <stdio.h>
#include <stdlib.h>

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


int main() {
    // Create new circular buffer.
    circular* c = circular_new(6);
    printf("start: %zu, len: %zu, max_len: %zu\n", c->start, circular_getlength(c), c->max_len);

    // Append some items.
    puts("\nAppending 5, 6, 7");
    circular_append(c, 5);
    circular_append(c, 6);
    circular_append(c, 7);
    printf("start: %zu, len: %zu, max_len: %zu\n", c->start, circular_getlength(c), c->max_len);
    printf("Element in pos 1 is: %.2f\n", *circular_element(c, 1));

    // Pop an item.
    printf("\nPopping element: %.2f\n", circular_pop(c));
    printf("start: %zu, len: %zu, max_len: %zu\n", c->start, circular_getlength(c), c->max_len);
    printf("Element in pos 1 is: %.2f\n", *circular_element(c, 1));


    // Test wrap-around.
    puts("\nTesting wraparound, appending 8, 9, 10, 11 (11 should be in pos 0)");
    circular_append(c, 8);
    circular_append(c, 9);
    circular_append(c, 10);
    circular_append(c, 11);

    puts("Check we cannot append anymore:");
    if(!circular_append(c, 12)) {
        puts("Nullpointer returned");
    }

    puts("Now pop 5 times");
    for (size_t i = 0; i < 5; i++) {
        printf("Popping element: %.2f\n", circular_pop(c));
        printf("start: %zu, len: %zu, max_len: %zu\n", c->start, circular_getlength(c), c->max_len);
    }
    printf("Element in pos 0 is: %.2f\n", *circular_element(c, 0));

    // Check popping empty array
    circular_pop(c); // Remove remaining item;
    puts("\nPopping empty array");
    printf("%.2f\n", circular_pop(c));

    // Delete buffer.
    circular_delete(c);
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