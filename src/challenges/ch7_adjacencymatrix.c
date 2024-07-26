/*
Modern C challenge 7: adjacency matrix.
I've implemented the three things mentioned in the book: breath-first search, connected components & spanning tree.
I've used malloc for the spanning tree, you can edit it to pass an array for the tree if you don't want to use malloc yet.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define N_nodes 8

void bfs(size_t N, const bool m[N][N], size_t root, bool visited[N]);
void connected_components(size_t N, bool m[N][N], bool visited[N]);
size_t* spanning_tree(size_t N, bool m[N][N]);
void printArray(size_t arr[], size_t length);

int main() {
    bool A[N_nodes][N_nodes] = {{false, true, false, false, false, false, true, false},
                    {true, false, false, false, true, true, true ,true},
                    {false, false, false, true, true, false, true, false},
                    {false, false, true, false, true, false, true, false},
                    {false, true, true, true, false, true, true, true},
                    {false, true, false, false, true, false, true, true},
                    {true, true, true, true, true, true, false, true},
                    {false, true, false, false, true, true, true, false}};

    bool B[N_nodes][N_nodes] = {{false, true, false, false, false, false, true, false},
                    {true, false, false, false, true, true, true ,true},
                    {false, false, false, true, false, false, false, false},
                    {false, false, true, false, false, false, false, false},
                    {false, true, false, false, false, true, true, true},
                    {false, true, false, false, true, false, true, true},
                    {true, true, false, false, true, true, false, true},
                    {false, true, false, false, true, true, true, false}};

    puts("BFS for matrix A from root = 0:");
    bool v1[N_nodes] = {0};
    bfs(N_nodes, A, 0, v1);
    printf("\n");

    puts("Connected components for matrix B");
    bool v2[N_nodes] = {0};
    connected_components(N_nodes, B, v2);

    puts("Spanning tree for matrix A");
    size_t* stree = spanning_tree(N_nodes, A);
    printArray(stree, N_nodes);
    free(stree);

    return EXIT_SUCCESS;
}


// BFS for adjacency matrix, prints visit order.
void bfs(size_t N, const bool m[N][N], size_t root, bool visited[N]) {
    assert(root < N);
    size_t queue[N];
    size_t l = 0; size_t r = 0;
    for (size_t i = 0; i < N; i++) {
        queue[i] = 0;
    }
    queue[r++] = root;
    visited[root] = true;
    printf("Root is: %zu\n", root);
    while (l < r) {
        size_t current = queue[l++];
        for (size_t i = 0; i < N; i++) {
            if (m[current][i] && !visited[i]) {
                queue[r++] = i;
                visited[i] = true;
                printf("Visited: %zu\n", i);
            }
        }
    }
}


// Find an print connected components for adjacency matrix.
void connected_components(size_t N, bool m[N][N], bool visited[N]) {
    size_t component_count = 1;
    for (size_t i = 0; i < N; i++) {
        if (!visited[i]) {
            printf("Component %zu:\n", component_count++);
            bfs(N, m, i, visited);
            printf("\n");
        }
    }
}


// Create a spanning tree for adjacency matrix
size_t* spanning_tree(size_t N, bool m[N][N]) {
    // Note: I just copied bfs here, you can be clever about reusing code, but I'm not going to bother.
    size_t queue[N];
    size_t* stree = malloc(N * sizeof(size_t)); // Store spanning tree in dynamic array -> do not forget to free after calling.
    bool visited[N];
    size_t l = 0; size_t r = 0;
    for (size_t i = 0; i < N; i++) {
        queue[i] = 0;
        visited[i] = false;
        stree[i] = SIZE_MAX;
    }
    queue[r++] = 0;     // Use root 0 -> graph needs to be connected for a spanning tree to exist.
    visited[0] = true;
    while (l < r) {
        size_t current = queue[l++];
        for (size_t i = 0; i < N; i++) {
            if (m[current][i] && !visited[i]) {
                queue[r++] = i;
                visited[i] = true;
                stree[i] = current;
            } 
        }
    }
    // Check if graph is connected.
    for (size_t i = 0; i < N; i++) {
        if (!visited[i]) { 
            fprintf(stderr, "Graph is not connected.\n");
            break;
        }
    }
    return stree;
}


// Utility for printing the array.
void printArray(size_t arr[], size_t length) {
    printf("[ ");
    for (int i = 0; i<length; i++) {
        printf("%zu ", *(arr+i));
    }
    printf("]\n");
}