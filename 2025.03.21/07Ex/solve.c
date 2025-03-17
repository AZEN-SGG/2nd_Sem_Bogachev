#include "solve.h"
#include <math.h>

#define eps 1e-17

int t7_solve(double *a, int m, int n)
{
	int min_j = 0;
	double minimum = 0;
	double inm = 1./m;

	for (int j = 0; j < n; j++)
	{
		double sum = 0;
		double avg = 0;
		for (int k = 0; k < m; k++) avg += a[k*n + j];
		avg *= inm;

		for (int i = 0; i < m; i++)
		{
			double temp = (a[i*n + j] - avg);
	       		sum += temp * temp;
		}	

		if ((minimum - sum) > eps || j == 0) { minimum = sum; min_j = j; }
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
