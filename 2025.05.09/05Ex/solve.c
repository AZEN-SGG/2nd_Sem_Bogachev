#include "solve.h"

#include <math.h>
#include <float.h>

double t5_solve (
		double (*f) (double), 
		double a, double b,
		int n	
) {
	const double h = (b - a) / (2 * n);
	double x = a;
	double sum = (f(a) + f(b)) * 0.5;

	if (h < NUM_FPE)
		return DBL_MAX;
	
	for (int i = 1; i < (2 * n - 1); ++i)
	{
		x += h;
		sum += ((i & 1) + 1) * f(x);
	}

	return (b - a) * sum / (3 * n);
}

