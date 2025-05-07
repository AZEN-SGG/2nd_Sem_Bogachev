#include "solve.h"

#include <math.h>
#include <float.h>

int t3_solve (
		double (*f) (double), 
		double x, double h 
) {
	if (h < DBL_EPSILON)
		return DBL_MAX;
	return (f(x + h) - 2 * f(x) + f(x - h)) / (h * h);
}

