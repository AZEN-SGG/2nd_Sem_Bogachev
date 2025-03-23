#include "solve.h"
#include "math.h"

void t8_solve(double *a, int n, int m, int i, int j, double g)
{
	int k;
	(void)n;
	for (k = 0; k < m; k++)
		a[j * m + k] += a[i * m + k] * g;
}
