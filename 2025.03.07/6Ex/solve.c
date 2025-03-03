#include "solve.h"
#include "math.h"

void t6_solve(double *a, int n, int m, int i, int j)
{
	double temp;
	int k;
	(void)n;
	for (k = 0; k < m; k++)
	{
		temp = a[i * m + k];
		a[i * m + k] = a[j * m + k];
		a[j * m + k] = temp;
	}
}
