#include "solve.h"
#include "math.h"

void matrix_multiply(const double *A, const double *B, double *c, int n, int m, int l)
{
	int i, j, k;
	for (i = 0; i < n; i++)
		for (k = 0; k < m; k++)
		{
			for (j = 0; j < l; j++)
			{
				if (k == 0) c[i * l + j] = 0;
				c[i * l + j] += A[i * m + k] * B[k * l + j];
			}
		}
}
