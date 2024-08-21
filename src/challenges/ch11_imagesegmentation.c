/*
Modern C challenge 11: Image Segmentation.

Note: Learning to build a library and link it in is a course in itself.
I have opted to write the code for reading and writing .bmp files myself.
Note that it only works with the 24-bit uncompressed .bmp format.

The UnionFind code is largly taken from challenge 4, and adapted to use the `region` struct.
You can control the segmentation by setting MERGE_DIST.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


#define MERGE_DIST 40

// Structs for bmp headers
typedef struct __attribute__((__packed__)) {
    uint16_t bfhSignature;
    uint32_t bfhSize;
    uint16_t bfhReserved1;
    uint16_t bfhReserved2;
    uint32_t bfhOffset;
} bmpFileHeader;

typedef struct __attribute__((packed)) {
    uint32_t bihHeaderSize;
    uint32_t bihWidth;
    uint32_t bihHeight;
    uint16_t bihPlanes;
    uint16_t bihPixelBits;
    uint32_t bihCompression;
    uint32_t bihImageSize;
    uint32_t bihDPIH;
    uint32_t bihDPIV;
    uint32_t bihColors;
    uint32_t bihImportantColors;
} bmpInfoHeader;

// Struct for segmentation region
typedef struct {
    size_t parent;
    unsigned char value;
    double average;
    size_t size;
} region;


// Function declarations
size_t find(region pixels[], size_t index);
size_t findCompress(region pixels[], size_t index);
bool Union(region pixels[], size_t left, size_t right);


int main() {
    // Open files
    FILE *inputFile = fopen("images/mark.bmp", "rb");
    FILE *outputFile = fopen("images/markgrey.bmp", "wb");
    if (inputFile == NULL) {
        perror("Error opening file!");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    // Read headers for bmpfile (Note: this can be done more compactly with packed, but we have not corered that yet.)
    bmpFileHeader fileHeader;
    fread(&fileHeader, sizeof(fileHeader), 1, inputFile);
    if (fileHeader.bfhSignature != 0x4D42) {
        fprintf(stderr, "Not a bitmap file");
        fclose(inputFile);
        fclose(outputFile);
        return EXIT_FAILURE;
    }
    bmpInfoHeader infoHeader;
    fread(&infoHeader, sizeof(infoHeader), 1, inputFile);

    // Populate image array
    fseek(inputFile, fileHeader.bfhOffset, SEEK_SET);
    unsigned char image[infoHeader.bihHeight][infoHeader.bihWidth];
    size_t rowPadding = ((4 - (infoHeader.bihPixelBits * infoHeader.bihWidth) % 4) % 4);
    for (size_t i = infoHeader.bihHeight - 1; i < infoHeader.bihHeight; i--) {
        unsigned char b = 0;
        unsigned char g = 0;
        unsigned char r = 0;
        for (size_t j = 0; j < infoHeader.bihWidth; j++) {
            fread(&b, 1, 1, inputFile);
            fread(&g, 1, 1, inputFile);
            fread(&r, 1, 1, inputFile);
            //0.299 ∙ Red + 0.587 ∙ Green + 0.114 ∙ Blue -> greyscale conversion
            unsigned char grey =  (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);
            image[i][j] = grey;
        }
        fseek(inputFile, rowPadding, SEEK_CUR);
    }

    // Copy and adapt headers
    bmpFileHeader fileHeaderOut;
    bmpInfoHeader infoHeaderOut;
    memcpy(&fileHeaderOut, &fileHeader, sizeof(fileHeader));
    memcpy(&infoHeaderOut, &infoHeader, sizeof(infoHeader));
    infoHeaderOut.bihPixelBits = 8;
    infoHeaderOut.bihColors = 256;
    size_t width = infoHeaderOut.bihWidth;
    size_t height = infoHeaderOut.bihHeight;
    size_t imgsize = width * height;
    infoHeaderOut.bihImageSize = imgsize;
    fileHeaderOut.bfhOffset = sizeof(bmpFileHeader) + sizeof(bmpInfoHeader) + 256 * 4;
    fileHeaderOut.bfhSize = fileHeaderOut.bfhOffset + imgsize;

    // Remember: union find structure is an array
    // Set up
    region* segmentation = malloc(imgsize * sizeof(region));
    for (size_t i = 0; i < imgsize; i++) {
        size_t row = i / width;
        size_t col = i % width;
        unsigned char val =  image[row][col];
        segmentation[i] = (region) {
            .parent = i,
            .value = val,
            .average = (double) val,
            .size = 1
        };
    }
  
    // Main loop
    size_t changes;
    do {
        // Perform Union
        changes = 0;
        for (size_t i = 0; i < height; i++) {
            for (size_t j = 1; j < width; j++) {
                size_t idx = (i * width) + j;

                if (Union(segmentation, idx-1, idx)) {
                    changes++;
                }
                if (i > 0) {
                    if (Union(segmentation, idx-width, idx)) {
                        changes++;
                    }
                }
            }
        }
        // Update image array
        for (size_t i = 0; i < imgsize; i++) {
            size_t root = segmentation[i].parent;
            size_t row = i / width;
            size_t col = i % width;
            image[row][col] = (unsigned char) segmentation[root].average;
        }
    } while (changes > 0);

    // Writing to file
    fwrite(&fileHeaderOut, 1, sizeof(fileHeaderOut), outputFile);
    fwrite(&infoHeaderOut, 1, sizeof(infoHeaderOut), outputFile);

    // Write grayscale palette
    for (int i = 0; i < 256; i++) {
        unsigned char palette[4] = {(unsigned char)i, (unsigned char)i, (unsigned char)i, 0};
        fwrite(palette, 1, 4, outputFile);
    }
    
    // Write output pixel data
    size_t rowPaddingOut = ((4 - (infoHeaderOut.bihPixelBits * width) % 4) % 4);
    for (size_t i = height - 1; i < height; i--) {
        fwrite(image[i], sizeof(unsigned char), width, outputFile);
        unsigned char padding[4] = {0};
        fwrite(padding, sizeof(unsigned char), rowPaddingOut, outputFile);
    }
    fclose(inputFile);
    fclose(outputFile);
    free(segmentation);
    return EXIT_SUCCESS;
}



// Find root of tree
size_t find(region pixels[], size_t index) {
    size_t i = index;
    while (pixels[i].parent != i) {
        i = pixels[i].parent;
    }
    return i;
}


// Compress tree
size_t findCompress(region pixels[], size_t index) {
    size_t root = find(pixels, index);
    size_t i = index;
    while (i != root) {
        size_t p = pixels[i].parent;
        pixels[i].parent = root;
        i = p;
    }
    return root;
}

// Merge two trees
bool Union(region pixels[], size_t left, size_t right) {
    size_t root_l = findCompress(pixels, left);
    size_t root_r = findCompress(pixels, right);
    if (root_l == root_r) {
        return false;
    }
    if (fabs(pixels[root_l].average - pixels[root_r].average) > MERGE_DIST) {
        return false;
    }
    pixels[root_r].parent = root_l;
    double avg_new = ((pixels[root_l].average * pixels[root_l].size) + (pixels[root_r].average * pixels[root_r].size)) /
                    (pixels[root_l].size + pixels[root_r].size);
    pixels[root_l].average = avg_new;
    pixels[root_l].size += pixels[root_r].size;
    return true;
}