#include "solve.h"
#include "math.h"

void t7_solve(double *a, int n, int m, int i, int j)
{
	double temp;
	int k;
	for (k = 0; k < n; k++)
	{
		temp = a[k * m + i];
		a[k * m + i] = a[k * m + j];
		a[k * m + j] = temp;
	}
}
