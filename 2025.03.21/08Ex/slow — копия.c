#include "solve.h"
#include <math.h>

#define eps 1e-17

int t8_solve(double *a, int m, int n)
{
	int max_i = 0, max_j = 0;
	double maximum = 0;

	for (int j = 0; j < n; j++)
	{
		double sum_j = 0;
		for (int k = 0; k < m; k++)
			sum_j += fabs(a[k*n + j]);
		
		for (int i = 0; i < m; i++)
		{
			double sum_i = 0;
			sum_j -= fabs(a[i*n + j]);

			for (int k = 0; k < n; k++) if (k != j)
				sum_i += fabs(a[i*n + k]);

			if (((sum_j + sum_i) - maximum) > eps)
				maximum = (sum_j + sum_i), max_i = i, max_j = j;
			
			sum_j += fabs(a[i*n + j]);
		}
	}

	for (int l = max_j+1, del_j = 1; l < max_i*n; l++)
	{
		if (l == ((n * del_j) + max_j))
			del_j++;
		else 
			a[l - del_j] = a[l];
	}

	for (int l = (max_i+1)*n, del_j = max_i; l < m*n; l++)
	{
		if (l == ((n * (del_j + 1)) + max_j))
			del_j++;
		else 
			a[l - del_j - n] = a[l];
	}

	return max_i * n + max_j;
}
