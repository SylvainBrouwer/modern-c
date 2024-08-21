/*
Modern C challenge 10: Performance comparison of sorting algorithms

Note that the code for the algorithms has been lifted from challenge 1.
The choice to stop arrsize at 2^17 is due to the default stack size. 
You can go further by increasing stack size with linker options or allocating on the heap.

Observed behaviour: Inconsistent (near 0) for low lengths, but roughly proportional with N log N for larger array sizes.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mergeSort(int list[], size_t l , size_t r);
void merge(int list[], size_t l, size_t r, size_t mid);
int partition(int list[], int l, int r);
void quickSort(int list[], int l, int r);
void swap(int *a, int *b);


int main() {
    // Initialize random number generator.
    srand(time(NULL));

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
        mergeSort(A, 0, arrsize-1);
        clock_t t2 = clock();
        clock_t t3 = clock();
        quickSort(B, 0, arrsize-1);
        clock_t t4 = clock();
        double diff1 = (double) (t2 - t1) / CLOCKS_PER_SEC;
        double diff2 = (double) (t4 - t3) / CLOCKS_PER_SEC;
        printf("For %zu elements:\n", arrsize);
        printf("Mergesort: %.5f\n", diff1);
        printf("Quicksort: %.5f\n", diff2);

    }
    return EXIT_SUCCESS;
}


void merge(int list[], size_t l, size_t r, size_t mid) {
    // Fill temp arrays
    size_t lsize = mid - l + 1;
    size_t rsize = r - mid;
    int L[lsize], R[rsize];
    for (size_t i = 0; i<lsize; i++) {
        L[i] = list[l+i];
    }
    for (size_t j = 0; j<rsize; j++) {
        R[j] = list[mid+1+j];
    }

    // Rearrange until one empty
    int i, j, k;
    i = j = 0;
    k = l;
    while (i < lsize && j <rsize) {
        if (L[i] <= R[j]) {
            list[k] = L[i];
            i++;
        } else {
            list[k] = R[j];
            j++;
        }
        k++;
    }

    // Dump rest
    while (i < lsize) {
        list[k] = L[i];
        i++;
        k++;
    }
    while (j < rsize) {
        list[k] = R[j];
        j++;
        k++;
    }
}


void mergeSort(int list[], size_t l, size_t r) {
    if (l < r) {
        size_t mid = l + ((r-l)/2); //Midpoint while avoiding int overflow.
        mergeSort(list, l, mid);
        mergeSort(list, mid+1, r);
        merge(list, l, r, mid);
    }
}


int partition(int list[], int l, int r) {
    int pivot = list[l];    // I choose pivot on the left.
    int i = l;
    int j = r;

    // Swap elements pointed to if left larger than pivot and right smaller than pivot.
    while (i < j) {
        while (list[i] <= pivot && i < r) {
            i++;
        }
        while (list[j] > pivot && j > l) {
            j--;
        }
        if (i < j) {
            swap(&list[i], &list[j]);
        }   
    }

    // Place pivot correctly
    swap(&list[l], &list[j]);
    return j;
}


void quickSort(int list[], int l, int r) {
    if (l<r) {
        int p = partition(list, l, r);
        quickSort(list, l, p-1);
        quickSort(list, p+1, r);
    }
}


// Swap two integers
void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}