/* 
Modern C challenge 14: Generic sorting.

To add functionality for new types: inplement a compare_X function.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ARRSIZE 10

typedef int compare_function(void const*, void const*);

void mergeSort(void* data, size_t n, size_t size, compare_function* compar);
void mergeSortInner(void* dst, void* data, size_t n, size_t size, compare_function* compar, size_t left, size_t right);
void merge(void* dst, void* data, size_t n, size_t size, compare_function* compar, size_t left, size_t mid, size_t right);
size_t partition(void* data, size_t n, size_t size, compare_function* compar, size_t left, size_t right);
void quickSortInner(void* data, size_t n, size_t size, compare_function* compar, size_t left, size_t right);
void quickSort(void* data, size_t n, size_t size, compare_function* compar);
int compare_int(void const* a, void const* b);

 

int main() {
    srand(time(NULL));

    int data[ARRSIZE] = {10, -3, 2, 5, 4, 11, 2, 7, 22, 3};
    puts("List mergesort:");
    for (size_t i = 0; i < ARRSIZE; i++) {
        printf("%d ", *(data+i));
    }
    printf("\n");
    mergeSort(data, ARRSIZE, sizeof(int), &compare_int);
    puts("Sorted: mergesort");
    for (size_t i = 0; i < ARRSIZE; i++) {
        printf("%d ", *(data+i));
    }
    printf("\n");

    int data2[ARRSIZE] = {-1, 31, 2, 3, 5, 6, 7, -20, 9, 10};
    puts("List quicksort:");
    for (size_t i = 0; i < ARRSIZE; i++) {
        printf("%d ", *(data2+i));
    }
    printf("\n");
    quickSort(data2, ARRSIZE, sizeof(int), &compare_int);
    puts("Sorted: quicksort");
    for (size_t i = 0; i < ARRSIZE; i++) {
        printf("%d ", *(data2+i));
    }
    printf("\n");

    // Performance comparison
    for (size_t arrsize = 2; arrsize < (1u << 18u); arrsize <<= 1u) {
        // Initialize array.
        int A[arrsize];
        int B[arrsize];
        for (size_t i = 0; i < arrsize; i++) {
            A[i] = rand();
            B[i] = rand();
        }

        // Time sorts.
        clock_t t1 = clock();
        mergeSort(A, arrsize, sizeof(int), &compare_int);
        clock_t t2 = clock();
        clock_t t3 = clock();
        quickSort(B, arrsize, sizeof(int), &compare_int);
        clock_t t4 = clock();
        double diff1 = (double) (t2 - t1) / CLOCKS_PER_SEC;
        double diff2 = (double) (t4 - t3) / CLOCKS_PER_SEC;
        printf("For %zu elements:\n", arrsize);
        printf("Mergesort: %.5f\n", diff1);
        printf("Quicksort: %.5f\n", diff2);
    }

    return EXIT_SUCCESS;
}


int compare_int(void const* a, void const* b) {
    int* x = (int*) a;
    int* y = (int*) b;
    if (*x < *y) {
        return -1;
    } else if (*x > *y) {
        return 1;
    }
    return 0;
}


void merge(void* dst, void* data, size_t n, size_t size, compare_function* compar, size_t left, size_t mid, size_t right) {
    size_t i = left;
    size_t j = mid;
    size_t k = left;
    unsigned char* source = (unsigned char*) data;
    unsigned char* target = (unsigned char*) dst;
    while (i < mid && j < right) {
        if (compar(source + i * size, source + j * size) <= 0) {
            memcpy(target + k * size, source + i * size, size);
            i++;
        } else {
            memcpy(target + k * size, source + j * size, size);
            j++;
        }
        k++;
    }
    while (i < mid) {
        memcpy(target + k * size, source + i * size, size);
        i++;
        k++;
    }
    while (j < right) {
        memcpy(target + k * size, source + j * size, size);
        j++;
        k++;
    }
    mempcpy(data+left*size, dst+left*size, size*(right-left));
}


void mergeSortInner(void* dst, void* data, size_t n, size_t size, compare_function* compar, size_t left, size_t right) {
    if (right < left || right - left < 2) {
        return;
    }
    size_t mid = left + (right-left) / 2;
    mergeSortInner(dst, data, n, size, compar, left, mid);
    mergeSortInner(dst, data, n, size, compar, mid, right);
    merge(dst, data, n, size, compar, left, mid, right);
}


void mergeSort(void* data, size_t n, size_t size, compare_function* compar) {
    if (!data) {
        return;
    }
    void* dst = malloc(size * n);
    if (dst) {
        mergeSortInner(dst, data, n, size, compar, 0, n);
        memcpy(data, dst, n*size);
    }
    free(dst);
}


size_t partition(void* data, size_t n, size_t size, compare_function* compar, size_t left, size_t right) {
    unsigned char* src = (unsigned char*) data;
    unsigned char* pivot = src+(left*size);
    size_t i = left;
    size_t j = right;
    unsigned char* tmp = malloc(size);
    // Swap elements pointed to if left larger than pivot and right smaller than pivot.
    while (i < j) {
        while (compar((src + i * size), pivot) <= 0 && i < right) {
            i++;
        }
        while (compar((src + j * size), pivot) > 0 && j > left) {
            j--;
        }
        if (i < j) {
            memcpy(tmp, (src + i * size), size);
            memcpy((src + i * size), (src + j * size), size);
            memcpy((src + j * size), tmp, size);
        }
    }
    memcpy(tmp, pivot, size);
    memcpy(pivot, (src + j * size), size);
    memcpy((src + j * size), tmp, size);
    free(tmp);
    return j;
}


void quickSortInner(void* data, size_t n, size_t size, compare_function* compar, size_t left, size_t right) {
    if (left < right && right < n) {
        size_t p = partition(data, n, size, compar, left, right);
        quickSortInner(data, n , size, compar, left, p-1);
        quickSortInner(data, n , size, compar, p+1, right);
    }
}


void quickSort(void* data, size_t n, size_t size, compare_function* compar) {
    quickSortInner(data, n, size, compar, 0, n-1);
}
