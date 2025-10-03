#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 500

// Function to allocate a matrix
double** allocate_matrix(int size) {
    double** matrix = (double**)malloc(size * sizeof(double*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (double*)malloc(size * sizeof(double));
    }
    return matrix;
}

// Function to free a matrix
void free_matrix(double** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to initialize matrix with random values
void initialize_matrix(double** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = (double)(rand() % 100);
        }
    }
}

// Inefficient matrix multiplication O(n^3)
void matrix_multiply_naive(double** A, double** B, double** C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Slightly optimized: cache-friendly version
void matrix_multiply_optimized(double** A, double** B, double** C, int size) {
    // Initialize result matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0.0;
        }
    }
    
    // Cache-friendly loop ordering
    for (int i = 0; i < size; i++) {
        for (int k = 0; k < size; k++) {
            double r = A[i][k];
            for (int j = 0; j < size; j++) {
                C[i][j] += r * B[k][j];
            }
        }
    }
}

int main() {
    printf("Matrix Multiplication Performance Test\n");
    printf("Matrix size: %dx%d\n\n", MATRIX_SIZE, MATRIX_SIZE);
    
    // Allocate matrices
    printf("Allocating matrices...\n");
    double** A = allocate_matrix(MATRIX_SIZE);
    double** B = allocate_matrix(MATRIX_SIZE);
    double** C = allocate_matrix(MATRIX_SIZE);
    
    // Initialize matrices
    printf("Initializing matrices...\n");
    initialize_matrix(A, MATRIX_SIZE);
    initialize_matrix(B, MATRIX_SIZE);
    
    // Perform naive multiplication
    printf("Performing naive matrix multiplication...\n");
    matrix_multiply_naive(A, B, C, MATRIX_SIZE);
    printf("Naive multiplication complete.\n");
    
    // Show a sample result
    printf("Sample result C[0][0] = %.2f\n", C[0][0]);
    
    // Clean up
    free_matrix(A, MATRIX_SIZE);
    free_matrix(B, MATRIX_SIZE);
    free_matrix(C, MATRIX_SIZE);
    
    printf("\nDone! Check the profile to see where time was spent.\n");
    return 0;
}
