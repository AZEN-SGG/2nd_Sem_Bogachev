#include "solve.h"
#include <math.h>
#include <float.h>
#include <stdio.h>

int t10_solve(double *a, int m, int n)
{
	int min_i = 0, min_j = 0;
	double minimum = DBL_MAX;
	double inn = 1./n, inm = 1./m;

	for (int i = 0; i < m; i++)
	{
		double cur = 0;
		double sum = 0;
		double sq_sum = 0;
		for (int j = 0; j < n; j++)
		{	
			double temp = a[i*n + j];
			sum += temp;
			sq_sum += temp * temp;
		}

		cur = sq_sum - (sum * sum) * inn;
		if ((minimum - cur) > DBL_EPSILON * fmax(fabs(minimum), fabs(cur))) {
			minimum = cur;
			min_i = i;
		}
	}

	minimum = DBL_MAX;
	for (int j = 0; j < n; j++)
	{
		const int BS = 32;
		double cur = 0;
		double sum = 0;
		double sq_sum = 0;

		for (int ii = 0; ii < m; ii += BS)
			for (int i = ii; i < ii + BS && i < m; i++)
			{
				double temp = a[i*n + j];
				sum += temp;
				sq_sum += temp * temp;
			}

		cur = sq_sum - (sum * sum) * inm;
		if ((minimum - cur) > DBL_EPSILON * fmax(fabs(minimum), fabs(cur))) {
			minimum = cur;
			min_j = j;
		}
	}
	
	for (int l = min_j+1, del_j = 1; l < min_i*n; l++)
	{
		if (l == ((n * del_j) + min_j))
			del_j++;
		else 
			a[l - del_j] = a[l];
	}

	for (int l = (min_i+1)*n, del_j = min_i; l < m*n; l++)
	{
		if (l == ((n * (del_j + 1)) + min_j))
			del_j++;
		else 
			a[l - del_j - n] = a[l];
	}

	return min_i * n + min_j;
}
