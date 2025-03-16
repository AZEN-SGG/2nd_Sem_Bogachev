#include "solve.h"
#include <math.h>

#define eps 1e-17

int t2_solve(double *a, int m, int n)
{
	int min_i = 0, min_j = 0;
	double minimum = (m * n > 0) ? fabs(a[0]) : 0;

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if ((minimum - fabs(a[i*n + j])) > eps) { minimum = fabs(a[i*n + j]); min_i = i; min_j = j; }

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
