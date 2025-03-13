#include "solve.h"
#include <math.h>

#define eps 1e-9

int compare(const double a, const double b)
{
	if (a - b > eps) return 1;
	else if (b - a > eps) return -1;
	return 0;
}

double t11_solve(double *a, int n, int m)
{
	int i, j, max_i = 0, max_j = 0;
	double temp = 0, maximum = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			if (compare(fabs(a[i*m + j]), maximum) == 1)
			{
				maximum = fabs(a[i*m + j]);
				max_i = i;
				max_j = j;
			}
	if (max_i != 0)	
		for (j = 0; j < m; j++)
		{
			temp = a[max_i*m+j];
			a[max_i*m+j] = a[j];
			a[j] = temp;
		}
	if (max_j != 0)
		for (i = 0; i < n; i++)
		{
			temp = a[i*m + max_j];
			a[i*m + max_j] = a[i*m];
			a[i*m] = temp;
		}

	return maximum;
}
