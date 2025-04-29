#include "init_f.h"

#include <math.h>

double f0 (double x)
{
	(void)x;

	return 1;
}

double f1 (double x)
{
	return (x * 1e-100) - 1.0;
}

double f2 (double x)
{
	return 4 - x * x;
}

double f3 (double x)
{
	double x_2 = x * x;

	return x * x_2 + 3 * x_2 + 16;
}

double f4 (double x)
{
	double x_2 = x * x;

	return 3 - 2 * x_2 - x_2 * x_2;
}

double f5 (double x)
{
	return sqrt(fabs(x) + 1) - 2;
}

double f6 (double x)
{
	return sqrt(sqrt(fabs(x) + 1) + 1) - 2;
}


