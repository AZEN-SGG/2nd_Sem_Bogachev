#include "solve.h"
#include "contin_func.h"

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

double dln (double x, const double eps)
{
	double value = 0;
	int b = 0;

	while (x - 2 > DBL_EPSILON)
	{
		x *= 0.5;
		b++;
	}
	
	while (x - 1 <= DBL_EPSILON)
	{
		x *= 2;
		b--;
	}
	
	value = fln(x, eps);

	value += b * M_LN2;
	return value;
}
