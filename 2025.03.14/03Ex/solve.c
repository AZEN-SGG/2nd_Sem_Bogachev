#include "solve.h"
#include "math.h"

double t3_solve(const double *A, const double *X, double *B, int m, int n)
{
	double r = 0;
	int i, j;
	for (i = 0; i < n; i++) B[i] = -B[i];

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			B[i] += A[i * m + j] * X[j];
		r += fabs(B[i]);
	}
	return r;
}

