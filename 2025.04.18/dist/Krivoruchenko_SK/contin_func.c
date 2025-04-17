#include "contin_func.h"

#include <math.h>
#include <float.h>

double ssin (const double x, const double eps)
{
	double value = 0;
	double el = x;
	int i = 1;

	while (fabs(el) - eps >= DBL_EPSILON)
	{
		value += el;

		el *= -(x*x / (i*i + 3*i + 2));
		i+=2;
	}
	
	return value;
}

double scos (const double x, const double eps)
{
	double value = 0;
	double el = 1;
	int i = 0;

	while (fabs(el) - eps >= DBL_EPSILON)
	{
		value += el;

		el *= - (x*x / (i*i + 3*i + 2));
		i+=2;
	}
	
	return value;
}
