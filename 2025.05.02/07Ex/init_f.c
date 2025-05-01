#include "init_f.h"

#include <math.h>


static int cl = 0;

int get_call_count (void) 
{
	return cl;
}

double f0 (double x)
{
	cl++;
	(void)x;

	return 1;
}

double f1 (double x)
{
	cl++;
	return ((x * 1e-100) - 1.0) * 1e100;
}

double f2 (double x)
{
	cl++;
	return 4 - x * x;
}

double f3 (double x)
{
	double x_2 = x * x;
	cl++;

	return x * x_2 + 3 * x_2 + 16;
}

double f4 (double x)
{
	double x_2 = x * x;
	cl++;

	return 3 - 2 * x_2 - x_2 * x_2;
}

double f5 (double x)
{
	cl++;
	return sqrt(fabs(x) + 1) - 2;
}

double f6 (double x)
{
	cl++;
	return sqrt(sqrt(fabs(x) + 1) + 1) - 2;
}


