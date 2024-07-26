/*
Modern C challenge 8: shortest path.
Since we are using size_t as our base type, we do not need to consider negative valued edges.

Note that I've split printing the shortest path from calculating distances.
dijkstra() calculates all distances from a specific node.
printReversePath() can then be used to print the path to a specific node, using the `parent` array.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N_nodes 7

void dijkstra(size_t N, size_t m[N][N], size_t start, size_t nodes[N], size_t parent[N]);
void printArray(size_t arr[], size_t length);
void printReversePath(size_t parent[], size_t start, size_t finish);

int main() {

    size_t A[N_nodes][N_nodes] = {{SIZE_MAX, 1, 3, SIZE_MAX, SIZE_MAX, 10, SIZE_MAX},
                                {1, SIZE_MAX, 1, 7, 5, SIZE_MAX, 2},
                                {3, 1, SIZE_MAX, 9, 3, SIZE_MAX, SIZE_MAX},
                                {SIZE_MAX, 7, 9, SIZE_MAX, 2, 1, 12},
                                {SIZE_MAX, 5, 3, 2, SIZE_MAX, 2, SIZE_MAX},
                                {10, SIZE_MAX, SIZE_MAX, 1, 2, SIZE_MAX, SIZE_MAX},
                                {SIZE_MAX, 2, SIZE_MAX, 12, SIZE_MAX, SIZE_MAX, SIZE_MAX}};

    size_t distances[N_nodes] = {0};
    size_t parent[N_nodes] = {0};
    dijkstra(N_nodes, A, 0, distances, parent);
    printArray(distances, N_nodes);
    printArray(parent, N_nodes);
    printReversePath(parent, 0, 5);
    return EXIT_SUCCESS;
}


void dijkstra(size_t N, size_t m[N][N], size_t start, size_t nodes[N], size_t parent[N]) {
    // Initialize
    bool visited[N];
    for (size_t i = 0; i < N; i++) {
        nodes[i] = SIZE_MAX;
        visited[i] = false;
        parent[i] = SIZE_MAX;
    }
    nodes[start] = 0;
    size_t current = start;

    while(true) {
        // Search unvisited node with smallest distance.
        size_t min_dist = SIZE_MAX;
        for (size_t i = 0; i < N; i++) {
            if (!visited[i] && nodes[i] < min_dist) {
                min_dist = nodes[i];
                current = i;
            }
        }

        // If no reachable unvisited notes -> return.
        if (min_dist == SIZE_MAX) {
            return;
        }
        // Mark current node as visited.
        visited[current] = true;


        // Update distances.
        for (size_t i = 0; i < N; i++) {
            if (m[current][i] == SIZE_MAX) {
                continue;
            }
            size_t dist_from_current = nodes[current] + m[current][i];
            if (!visited[i] && dist_from_current < nodes[i] ) {
                nodes[i] = dist_from_current;
                parent[i] = current;
            }
        }
    }
}


// Print reverse path using the `parent` array.
void printReversePath(size_t parent[], size_t start, size_t finish) {
    if (parent[finish] == SIZE_MAX && start != finish) {
        fprintf(stderr, "No path between nodes %zu and %zu exists\n", start, finish);
        return;
    }
    size_t current = finish;
    do {
        printf("-%zu", current);
        current = parent[current];
    } while (current != SIZE_MAX);
    printf("-\n");
}


// Utility for printing the array.
void printArray(size_t arr[], size_t length) {
    printf("[ ");
    for (int i = 0; i<length; i++) {
        printf("%zu ", *(arr+i));
    }
    printf("]\n");
}