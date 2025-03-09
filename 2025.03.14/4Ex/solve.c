#include "solve.h"
#include "math.h"

#define eps 1e-9

int compare(const double a, const double b)
{
	if (a - b > eps) return 1;
	else if (b - a > eps) return -1;
	return 0;
}

double t4_solve(const double *A, const double *X, double *B, int m, int n)
{
	double maximum = 0, cur;
	int i, j;

	for (i = 0; i < n; i++)
	{
		cur = -B[i];
		for (j = 0; j < m; j++)
			cur += A[i * m + j] * X[j];
		cur = fabs(cur);
		if (compare(cur, maximum) == 1) maximum = cur;
	}

	return maximum;
}

