#include "solve.h"
#include <math.h>

#define eps 1e-17

int t4_solve(double *a, int m, int n)
{
	int min_i = 0, min_j = 0;
	double minimum = -1;

	for (int i = 0; i < m; i++)
	{
		double sum = 0;
		for (int j = 0; j < n; j++)
			sum += fabs(a[i*n + j]);

		if ((minimum - sum) > eps || i == 0) { minimum = sum; min_i = i; }
	}

	for (int j = 0; j < n; j++)
	{
		double sum = 0;
		for (int i = 0; i < m; i++)
			sum += fabs(a[i*n + j]);

		if ((minimum - sum) > eps || j == 0) { minimum = sum; min_j = j; }
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
