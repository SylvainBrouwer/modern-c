#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 100

void setUp(size_t parent[], size_t size);
size_t find(size_t parent[], size_t index);
void findReplace(size_t parent[], size_t index, size_t value);
void findCompress(size_t parent[], size_t index);
void printArray(size_t arr[], size_t length);
void Union(size_t parent[], size_t left, size_t right);


int main() {
    size_t parent[TABLE_SIZE];
    setUp(parent, TABLE_SIZE);

    // Construct a more interesting tree: two chains
    // First create one long chain
    for (size_t i = 1; i<100; i++) {
        findReplace(parent, i, i-1);
    }
    parent[50] = SIZE_MAX; // Split chain
    printArray(parent, TABLE_SIZE);

    // Take union (leave one element dangling on each side, just for fun)
    Union(parent, 48, 98);
    printArray(parent, TABLE_SIZE);
}


// Set up singleton partition
void setUp(size_t parent[], size_t size) {
    for (size_t i = 0; i < size; i++) {
        parent[i] = SIZE_MAX;
    }
}


// Find root of tree
size_t find(size_t parent[], size_t index) {
    size_t i = index;
    while (parent[i] != SIZE_MAX) {
        i = parent[i];
    }
    return i;
}


// Set all entries on path to root to "value"
void findReplace(size_t parent[], size_t index, size_t value) {
    size_t i = index;
    do{
        size_t p = parent[i];
        parent[i] = value;
        i = p;
    } while(i != SIZE_MAX);
}


// Compress tree
void findCompress(size_t parent[], size_t index) {
    size_t root = find(parent, index);
    size_t i = index;
    while (i != root) {
        size_t p = parent[i];
        parent[i] = root;
        i = p;
    }    
}


// Merge two trees
void Union(size_t parent[], size_t left, size_t right) {
    findCompress(parent, left);
    size_t root = find(parent, left);
    findReplace(parent, right, root);
}


// Utility for printing the array
void printArray(size_t arr[], size_t length) {
    printf("[ ");
    for (size_t i = 0; i<length; i++) {
        printf("%zu: %zu\n", i, *(arr+i));
    }
    printf("]\n");
}