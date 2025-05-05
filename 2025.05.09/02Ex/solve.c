#include "solve.h"

#include <math.h>
#include <float.h>

int t2_solve (
		double (*f) (double), 
		double x, double h 
) {
	if (h < DBL_EPSILON)
		return DBL_MAX;
	return (f(x + h) - f(x - h)) / (2 * h);
}

