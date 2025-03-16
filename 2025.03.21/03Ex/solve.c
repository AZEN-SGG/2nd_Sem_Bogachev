#include "solve.h"
#include <math.h>

#define eps 1e-17

int t3_solve(double *a, int m, int n)
{
	int min_j = 0;
	double minimum = -1;

	for (int j = 0; j < n; j++)
	{
		double cur = 0;
		for (int i = 0; i < m; i++)
			cur += fabs(a[i*n + j]);	
		if ((minimum - cur) > eps || j == 0) { minimum = cur; min_j = j; }
	}

	for (int l = min_j+1, del_j = 1; l < m*n; l++)
	{
		if (l == ((n * del_j) + min_j))
			del_j++;
		else 
			a[l - del_j] = a[l];
	}

	return min_j + 1;
}
