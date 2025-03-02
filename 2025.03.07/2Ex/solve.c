#include "solve.h"
#include "math.h"

double t2_solve(double *a, int n)
{
	double trace = 0;
	int i;
	for (i = 0; i < n; i++)
		trace += a[i * n + i];
	return trace;
}
