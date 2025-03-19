#include "solve.h"
#include <math.h>

#define eps 1e-17

int t9_solve(double *a, int m, int n)
{
	const int BS = 32;
	int max_i = 0, max_j = 0;
	double maximum = 0;

	for (int jj = 0; jj < n; jj += BS)
		for (int ii = 0; ii < m; ii += BS)
			for (int j = jj; j < jj + BS && j < n; j++)
				for (int i = ii; i < ii + BS && i < m; i++)
				{
					double sum_i = 0;
					double sum_j = 0;
					double aij = a[i*n + j];
				
					for (int kk = 0; kk < n; kk += BS)
						for (int k = kk; k < kk + BS && k < n; k++) if (k != j)
							sum_i += fabs(a[i*n + k] - aij);
			
					for (int kk = 0; kk < m; kk += BS)
						for (int k = kk; k < kk + BS && k < m; k++) if (i != k)
							sum_j += fabs(a[k*n + j] - aij);
			
					if (((sum_j + sum_i) - maximum) > eps)
						maximum = (sum_j + sum_i), max_i = i, max_j = j;
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
