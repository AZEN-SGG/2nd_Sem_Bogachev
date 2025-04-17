#include "contin_func.h"

#include <math.h>
#include <float.h>

double sexp (const double x, const double eps)
{
	double value = 1;
	double monom = x;
	int i = 1;

	while (monom - eps >= DBL_EPSILON)
	{
		value += monom;

		i++;
		monom *= x/i;
	}

	return value;
}
