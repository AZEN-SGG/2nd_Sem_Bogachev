#include "solve.h"
#include <math.h>

#define eps 1e-17

int t1_solve(double *a, int m, int n)
{
	int l, min_i = 0, min_j = 0, del_j;
	double minimum = (m * n > 0) ? fabs(a[0]) : 0;

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if ((minimum - fabs(a[i*n + j])) > eps) { minimum = fabs(a[i*n + j]); min_i = i; min_j = j; }

	(void)(min_i);

	for (l = min_j+1, del_j = 1; l < m*n; l++)
	{
		if (l == ((n * del_j) + min_j))
			del_j++;
		else 
			a[l - del_j] = a[l];
	}

	return min_j + 1;
}
