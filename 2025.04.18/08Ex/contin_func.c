#include "contin_func.h"

#include <math.h>
#include <float.h>

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

double sln (const double x, const double eps)
{
	const double z = x - 1;
	double value = 0;
	double monom = z, el = z;
	int i = 1;

	while (fabs(el) - eps > DBL_EPSILON)
	{
		value += el;

		i++;
		monom *= -z;
		el = monom / i;
	}

	return value;
}
