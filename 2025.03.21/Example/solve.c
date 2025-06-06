#include "solve.h"
#include <math.h>

#define eps 1e-17

int compare(const double a, const double b)
{
	if (a - b > eps) return 1;
	else if (b - a > eps) return -1;
	return 0;
}

double t1_solve(double *a, int m, int n)
{
	int i, j;
	double cur = 0, maximum = 0;
	
	for (i = 0; i < n; i++)
	{
		cur = 0;
		for (j = 0; j < m; j++)
			cur += fabs(a[i * m + j]);
		if (compare(cur, maximum) == 1) maximum = cur;
	}

	return maximum;
}
