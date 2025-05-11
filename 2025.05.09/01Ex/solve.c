#include "solve.h"

#include <math.h>
#include <float.h>

double t1_solve (
		double (*f) (double), 
		double x, double h 
) {
	if (h < NUM_FPE)
		return DBL_MAX;
	return (f(x + h) - f(x)) / h;
}

