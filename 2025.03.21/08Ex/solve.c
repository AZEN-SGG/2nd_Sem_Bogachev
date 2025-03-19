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
			double aij = fabs(a[i*n + j]);
			sum_j -= aij;

			if (j == 0)
			{
				double num = a[i*n];
				for (int k = 1; k < n; k++)
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
		for (int i = 0; i < m; i++)
		{
			double orig = a[i*n];
			double num = fabs(orig);

			for (int j = 1; j < n; j++)
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
