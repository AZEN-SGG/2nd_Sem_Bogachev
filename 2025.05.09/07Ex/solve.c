#include "solve.h"
#include "comp.h"

#include <math.h>
#include <float.h>

double t7_solve (
		double (*f) (double), 
		double a, double b,
		int n	
) {
	const double h = (b - a) / (2 * n);
	double x = a;
	double sum;

	if (is_null(a) || is_null(b))
		return DBL_MAX;

	f_global = f;
       	sum = (wf(a) + wf(b)) * 0.5;

	if (h < NUM_FPE)
		return DBL_MAX;
	
	for (int i = 1; i < (2 * n - 1); ++i)
	{
		x += h;
		if (is_null(x))
			return DBL_MAX;
		sum += ((i & 1) + 1) * wf(x);
	}

	return (b - a) * sum / (3 * n);
}

