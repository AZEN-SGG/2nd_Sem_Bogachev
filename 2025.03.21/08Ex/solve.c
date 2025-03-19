#include "solve.h"
#include <math.h>

#define eps 1e-17

int t8_solve(double *a, int m, int n)
{
	const int BS = 30;
	int max_i = 0, max_j = 0;
	double maximum = 0;
	
	for (int jj = 0; jj < n; jj += BS)
		for (int j = jj; j < jj + BS && j < n; j++)
			{
				double sum_j = 0;
				for (int ii = 0; ii < m; ii += BS) 
					for (int k = ii; k < ii + BS && k < m; k++)
						sum_j += fabs(a[k*n + j]);
			
				for (int ii = 0; ii < m; ii += BS) 
					for (int i = ii; i < ii + BS && i < m; i++)
					{
						double sum_i = 0;
						double aij = fabs(a[i*n + j]);
						sum_j -= aij;

						if (j == 0)
						{
							double num = a[i*n];
							for (int kk = 1; kk < n; kk += BS)
								for (int k = kk; k < kk + BS && k < n; k++)
									sum_i += fabs(a[i*n + k]);

							a[i*n] = copysign(fabs(num) + sum_i, num);
						}
						else
							sum_i = fabs(a[i*n]) - fabs(a[i*n + j]);
	
						if (((sum_j + sum_i) - maximum) > eps)
							maximum = (sum_j + sum_i), max_i = i, max_j = j;
			
						sum_j += aij;
					}
			}

	if (max_j != 0)
		for (int ii = 0; ii < m; ii += BS)
			for (int i = ii; i < ii + BS && i < m; i++)
			{
				double orig = a[i*n];
				double num = fabs(orig);
				
				for (int jj = 1; jj < n; jj += BS)
					for (int j = jj; j < jj + BS && j < n; j++)
						num -= fabs(a[i*n + j]);

				a[i*n] = copysign(num, orig);
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
