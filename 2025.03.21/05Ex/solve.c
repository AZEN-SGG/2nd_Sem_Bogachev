#include "solve.h"
#include <math.h>
#include <float.h>
#include <stdio.h>

int t5_solve(double *a, int m, int n)
{
	int max_j = 0;
	double maximum = 0;

	for (int j = 0; j < n; j++)
	{
		double sum = 0;
		for (int i = 0; i < m; i++)
			if (i != j)
				sum += fabs(a[i*n + j]);
		
		if ((sum - maximum) > DBL_EPSILON * fmax(fabs(maximum), fabs(sum))) { maximum = sum; max_j = j; }
	}

	for (int l = max_j+1, del_j = 1; l < m*n; l++)
	{
		if (l == ((n * del_j) + max_j))
			del_j++;
		else 
			a[l - del_j] = a[l];
	}

	return max_j + 1;
}
