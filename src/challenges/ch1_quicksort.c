/*
Modern C challenge 1 part 2: quicksort
I've chosen ints, but the process should be the same for floats / doubles
*/
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

// Function declarations
int partition(int list[], int l, int r);
void quickSort(int list[], int l, int r);
void swap(int *a, int *b);
void printArray(int arr[], size_t length);


int main() {
    int mylist[] = {100, -2, 2, 0, 78, -20000, 98, 453, 201};
    size_t length  = sizeof(mylist) / sizeof(mylist[0]);
    printf("Before: ");
    printArray(mylist, length);

    // Sort
    quickSort(mylist, 0, length-1);
    printf("After: ");
    printArray(mylist, length);
    return 0;
}


int partition(int list[], int l, int r) {
    int pivot = list[l];    // I choose pivot on the left.
    int i = l;
    int j = r;

    // Swap elements to correct side of.
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


// Utility for printing the array
void printArray(int arr[], size_t length) {
    printf("[ ");
    for (int i = 0; i<length; i++) {
        printf("%d ", *(arr+i));
    }
    printf("]\n");
}