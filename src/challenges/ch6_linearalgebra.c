/*
Modern C challenge 6: linear algebra.
I've implemented a dot product, matrix vector product, gaussian elimination and a matrix inverse.
Note that I skipped ahead to using malloc for invert, because I did not feel like passing an intermediary array as a parameter.
*/
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>

#define M_size 3
#define N_size 3

double dot_product(size_t N, const double a[N], const double b[N]);
void mat_vec_product(size_t N, size_t M, const double m[M][N], const double v[N], double result[M]);
void gaussian_elimination(size_t N, size_t M, double m[M][N]);
void swapRow(double* r1, double* r2, size_t length);
void invert(size_t N, const double m[N][N], double result[N][N]);
void printArray(double arr[], size_t length);
void printMatrix(size_t N, size_t M, double m[static M][N]);


int main() {
    // Dot product
    double v1[N_size] = {1.4, 2.2, 1.0};
    double v2[N_size] = {5, 3.2, 2.0};
    double v3 = dot_product(N_size, v1, v2);
    puts("Printing vector v1:");
    printArray(v1, N_size);
    puts("Printing vector v2:");
    printArray(v2, N_size);
    printf("Resulting dot product: %f\n", v3);

    // Matrix-vector product.
    double m[M_size][N_size] = {{1, 0, 0},
                                {3, 3, 0},
                                {5, 2, -1}};

    puts("Printing matrix m:");
    printMatrix(N_size, M_size, m);
    double result[M_size] = {0};
    mat_vec_product(N_size, M_size, m, v1, result);
    puts("Matrix vector product m*v1:");
    printArray(result, M_size);

    // Invert matrix
    double inverse[M_size][N_size] = {0};
    invert(N_size, m, inverse);
    puts("Inverse:");
    printMatrix(N_size, N_size, inverse);
    
    // Gaussian elimination on matrix.
    puts("Reduced row echelon form:");
    gaussian_elimination(N_size, M_size, m);
    printMatrix(N_size, M_size, m);
    return EXIT_SUCCESS;
}


// Dot product of two vectors.
double dot_product(size_t N, const double a[N], const double b[N]) {
    double result = 0.0;
    for (size_t i=0; i<N; i++) {
        result += a[i]*b[i];
    }
    return result;
}


// Note that I pass a result vector -> we have not learned VLAs / malloc yet.
void mat_vec_product(size_t N, size_t M, const double m[M][N], const double v[N], double result[M]) {
    for (size_t i=0; i<M; i++) {
        result[i] = dot_product(N, m[i], v);
    }
}


// Gaussian elimination -> reduced row echelon form. Note that this is in-place.
void gaussian_elimination(size_t N, size_t M, double m[M][N]) {
    size_t row = 0;
    size_t col = 0;
    while (row < M && col < N) {
        // Look for pivot
        double max = DBL_MIN;
        double pivotvalue = 0;
        size_t pivot = row;
        for (size_t i = row; i < M; i++) {
            if (fabs(m[i][col]) > max) {
                pivotvalue = m[i][col];
                max = fabs(m[i][col]);
                pivot = i;
            }
        }
        if (fabs(m[pivot][col]) < 1e-6) {
            // No pivot found, pass to next column.
            col++;
        } else {
            // Reduce other rows using pivot row.
            swapRow(m[row], m[pivot], N);
            for (size_t i = 0; i<M; i++) {
                if (i != row) {
                    double frac = m[i][col] / m[row][col];
                    for (size_t j = col; j < N; j++) {
                        m[i][j] = m[i][j] - m[row][j] * frac;
                    }
                }
            }
            // Normalize pivot row so that pivot is 1.
            for (size_t j = col; j < N; j++) {
                m[row][j] = m[row][j] / pivotvalue;
            }
            row++;
            col++;
        }
    }
}


void invert(size_t N, const double m[N][N], double result[N][N]) {
    // Build augmented matrix [A|I].
    double (*aug)[2*N] = malloc(N * sizeof(double[2*N]));
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < 2*N; j++) {
            if (j < N) {
                aug[i][j] = m[i][j];
            } else {
                if (i+N == j) {
                    aug[i][j] = 1;
                } else {
                    aug[i][j] = 0;
                }
            }
        }
    }
    // Gaussian elimination [A|I] -> [B|I].
    gaussian_elimination(2*N, N, aug);

    // Check that matrix was invertible.
    bool invertible = true;
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            if (i == j && aug[i][j] != 1){
                invertible = false;
                break;
            } else if (i != j && aug[i][j] != 0) {
                invertible = false;
                break;
            }
            
        }
    }
    if (!invertible) {
        // Exit and report error if matrix was not invertible.
        fprintf(stderr, "Matrix is not invertible, result matrix unchanged!\n");
        free(aug);
        return;
    }

    // Extract B from [I|B].
    for (size_t i = 0; i < N; i++) {
        for (size_t j = N; j < 2*N; j++) {
            result[i][j-N] = aug[i][j];
        }
    }
    free(aug);
}


// Swap values in two provided arrays.
void swapRow(double* r1, double* r2, size_t length) {
    for (int i = 0; i < length; i++) {
        double temp = r1[i];
        r1[i] = r2[i];
        r2[i] = temp;
    }
}


// Utility for printing the array.
void printArray(double arr[], size_t length) {
    printf("[ ");
    for (int i = 0; i<length; i++) {
        printf("%f ", *(arr+i));
    }
    printf("]\n");
}


// Utility for printing a matrix.
void printMatrix(size_t N, size_t M, double m[static M][N]) {
    printf("[\n");
    for (int i = 0; i < M; i++) {
        printArray(m[i], N);
    }
    printf("]\n");
}