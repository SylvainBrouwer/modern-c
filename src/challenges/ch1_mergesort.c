/*
Modern C challenge 1 part 1: Merge sort.
I've chosen ints, but the process should be the same for floats / doubles
*/
#include <stdio.h>
#include <stddef.h>

// Function declarations
void mergeSort(int list[], size_t l , size_t r);
void merge(int list[], size_t l, size_t r, size_t mid);
void printArray(int arr[], size_t length);


int main() {
    // Example array
    int mylist[] = {9, 7, 3, 23, 1, -3, 20000, 0, 99, 2, 76, -100};
    size_t length = sizeof(mylist) / sizeof(mylist[0]);
    printf("Before: ");
    printArray(mylist, length);

    // Sort
    mergeSort(mylist, 0, length-1);
    printf("After: ");
    printArray(mylist, length);
    return 0;
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


// Utility for printing the array
void printArray(int arr[], size_t length) {
    printf("[ ");
    for (size_t i = 0; i<length; i++) {
        printf("%d ", *(arr+i));
    }
    printf("]\n");
}