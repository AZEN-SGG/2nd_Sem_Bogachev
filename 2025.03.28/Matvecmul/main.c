#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solve.h"

// Прототип вашей функции перемножения
void multiply_matrix_vector(int n, double** matrix, double* vector, double* result);

int main(int argc, char* argv[]) {
    int n, i, j;
    double* matrix;
    double* vector;
    double* result;
    clock_t start, end;
    double elapsed;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "n must be a positive integer\n");
        return 1;
    }

    matrix = (double*)malloc(n * n * sizeof(double));
    vector = (double*)malloc(n * sizeof(double));
    result = (double*)malloc(n * sizeof(double));

    srand((unsigned int)time(NULL));

    for (i = 0; i < n; ++i) {
        vector[i] = rand() % 10;
        for (j = 0; j < n; ++j)
            matrix[i*n + j] = rand() % 10;
    }

    start = clock();
	
    matvec_mul(n, matrix, vector, result);

    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Result vector:\n");
    for (i = 0; i < (n > 5 ? 5 : n); ++i)
        printf("%.2f ", result[i]);
    printf("\n");

    printf("Elapsed time: %.6f seconds\n", elapsed);

    free(matrix);
    free(vector);
    free(result);

    return 0;
}
