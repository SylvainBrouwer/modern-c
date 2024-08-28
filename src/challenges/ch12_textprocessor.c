/*
Modern C challenge 12: Text Processor

I've decided to just use a string as input, you could also read from a file.
I use malloc liberally, even though the book technically hasn't covered it yet.
Consider learning malloc it part of the "challenge".
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct blob blob;
struct blob {
    char* content;
    blob* previous;
    blob* next;
};


blob* get_blob(char* string);
blob* split_blob(blob* bp, size_t split);
blob* merge_with_next(blob* bp);
blob* split_on_newline(blob* bp);
void cleanup_list(blob* bp);
void cleanup_blob(blob* bp);
void print_all_blobs(blob* bp);


int main() {
    // Create initial blob
    char text[] = "This is sentence number one.\n"
                    "This is sentence number two.\n"
                    "This is sentence number three.\n"
                    "This is the last sentence of my sample text";
    blob* bp = get_blob(text);
    printf("Initial string:\n%s\n", bp->content);

    // Test split
    size_t split = 25;
    if (!split_blob(bp, split)) {
        free(bp);
        return EXIT_FAILURE;
    }
    printf("\nFirst node after spliting at %zu:\n%s\n", split, bp->content);
    printf("Second node after spliting at %zu:\n%s\n", split, bp->next->content);

    // Test merge
    merge_with_next(bp);
    printf("\nAfter merging again:\n%s\n", bp->content);

    // Test split newline
    puts("\nSplitting on new lines!");
    split_on_newline(bp);
    blob* current = bp;
    do {
        printf("Node: %s\n", current->content);
        current = current->next;
    } while (current);

    
    // Printing all blobs
    puts("\nPrinting all blobs:");
    print_all_blobs(bp);


    // Free list
    cleanup_list(bp);
    return EXIT_SUCCESS;
}


blob* get_blob(char* string) {
    blob* bp = malloc(sizeof(blob));
    bp->content = strdup(string);
    bp->previous = 0;
    bp->next = 0;
    return bp;
}


blob* split_blob(blob* bp, size_t split) {
    size_t length = strlen(bp->content);
    if (split > length) {
        errno = EINVAL;
        perror("Can't split beyond content string");
        return 0;
    }
    // Extract string for new blob and create blob.
    char* new_content = malloc(length-split+1);
    new_content = strdup(bp->content+split);
    blob* new_blob = get_blob(new_content);

    // Truncate string for existing blob.
    char* remaining_content = malloc(split+1);
    strncpy(remaining_content, bp->content, split);
    remaining_content[split] = '\0';
    free(bp->content);
    bp->content = remaining_content;

    // Update next / previous pointers
    if(bp->next) {
        bp->next->previous = new_blob;
        new_blob->next = bp->next;
    }
    new_blob->previous = bp;
    bp->next = new_blob;
    return bp->next;
}


blob* split_on_newline(blob* bp) {
    blob* current = bp;
    size_t split = strcspn(current->content, "\n");
    while (split < strlen(current->content)) {
        split_blob(current, split+1);   // I keep the newline in the current blob.
        current = current->next;
        split = strcspn(current->content, "\n");
    }
    return bp;
}


// Merges the blob at address bp with the following blob
blob* merge_with_next(blob* bp) {
    if (!bp || !bp->next) {
        fprintf(stderr, "Can't merge: need two consecutive blobs.\n");
        return bp;
    }
    char* merged_content = malloc(strlen(bp->content) + strlen(bp->next->content) + 1);
    strcpy(merged_content, bp->content);
    strcat(merged_content, bp->next->content);
    free(bp->content);
    bp->content = merged_content;
    blob* new_next = bp->next->next;
    cleanup_blob(bp->next);
    bp->next = new_next;
    if (new_next) {
        new_next->previous = bp;
    }
    return bp;
}


void cleanup_list(blob* bp) {
    if (bp == 0) {
        return;
    }
    blob* current = bp;
    // Find head of list.
    while (current->previous != 0) {
        current = current->previous;
    }
    // Free all blobs.
    while (current != 0) {
        blob* previous = current;
        current = current->next;
        cleanup_blob(previous);
    };
}


// Free a blob and its contents.
void cleanup_blob(blob* bp) {
    if (bp == 0) {
        return;
    }
    free(bp->content);
    free(bp);
}


void print_all_blobs(blob* blob) {
    if (blob) {
        if (blob->content) {
            printf("%s", blob->content);
        }
        print_all_blobs(blob->next);
    }
}