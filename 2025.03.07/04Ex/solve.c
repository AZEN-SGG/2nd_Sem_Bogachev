#include "solve.h"
#include "math.h"

void t4_solve(double *a, int n)
{
	double temp;
	int i, j;
	for (i = 0; i < n; i++)
		for (j = i; j < n; j++)
			if (i != j) {
				temp = a[i * n + j];
				a[i * n + j] = (a[j * n + i] + temp) / 2;
				a[j * n + i] = (a[j * n + i] + temp) / 2;
			}		
}
