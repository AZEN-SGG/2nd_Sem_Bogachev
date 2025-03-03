#include "solve.h"
#include "math.h"

void matrix_multiply(const double *A, const double *B, double *c, int n, int m, int l)
{
	int i, j, k, index;
	for (i = 0; i < n; i++)
		for (j = 0; j < l; j++)
		{
			index = i * l + j;
			c[index] = 0;
			for (k = 0; k < m; k++)
				c[index] += A[i * m + k] * B[k * l + j];
		}
}
