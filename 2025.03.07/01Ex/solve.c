#include "solve.h"
#include "math.h"

#define eps 1e-6

int t1_solve(double *a, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = i; j < n; j++)
			if (i != j)
				if (fabs(a[i * n + j] - a[j * n + i]) > eps) return 0;
	return 1;
}
