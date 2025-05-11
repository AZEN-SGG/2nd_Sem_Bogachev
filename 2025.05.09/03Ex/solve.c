#include "solve.h"

#include <math.h>
#include <float.h>

double t3_solve (
		double (*f) (double), 
		double x, double h 
) {
	double h_2 = h * h;
	if (h_2 < NUM_FPE)
		return DBL_MAX;
	return (f(x + h) - 2 * f(x) + f(x - h)) / h_2;
}

