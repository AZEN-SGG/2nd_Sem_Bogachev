#include "solve.h"
#include "contin_func.h"

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

double fexp (double x, const double eps)
{
	double integral, fractal, answer = 1;
	bool is_negative = false;

	if (x < DBL_EPSILON)
	{
		is_negative = true;
		x = -x;
	}

	integral = floor(x);
	fractal = x - integral;

	for (double i = 0; (integral - i) > DBL_EPSILON; ++i)
		answer *= M_E;

	answer *= sexp(fractal, eps);
	if (is_negative)
		answer = 1. / answer;

	return answer;
}
