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

double fln (const double x, const double eps)
{
	const double z = (x - 1) / (x + 1);
	double value = 0;
	double monom = z, el = z;
	int i = 1;

	while (el - eps > DBL_EPSILON)
	{
		value += el;

		i+=2;
		monom *= z*z;
		el = monom / i;
	}

	return 2 * value;
}