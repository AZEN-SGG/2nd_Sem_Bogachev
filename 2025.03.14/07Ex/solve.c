#include "solve.h"
#include <math.h>

#define eps 1e-9

int compare(const double a, const double b)
{
	if (a - b > eps) return 1;
	else if (b - a > eps) return -1;
	return 0;
}

double t7_solve(double *a, int n, int m)
{
	int i, j;
	double cur = 0, maximum = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			if (i == 0 || i == n-1 || j == 0 || j == m-1)
				if (compare(fabs(a[i*m + j]), maximum) == 1)
					maximum = fabs(a[i*m + j]);
	
	for (i = 1; i < n-1; i++)
		for (j = 1; j < m-1; j++)
		{
			cur = (a[(i-1)*m + j] + a[(i+1)*m + j] + a[i*m + (j-1)] + a[i*m + (j+1)]) / 5;
			if (compare(fabs(cur), maximum) == 1) maximum = fabs(cur);
			a[i*m + j] = cur;
		}

	return maximum;
}
