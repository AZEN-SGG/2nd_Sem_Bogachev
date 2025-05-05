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
	return x + 1;
}

double f2 (double x)
{
	cl++;
	return x * x + x + 1;
}

double f3 (double x)
{
	double x_2 = x * x;
	cl++;

	return x * x_2 + x_2 + x + 1;
}

double f4 (double x)
{
	double x_2 = x * x;
	double x_3 = x_2 * x;
	cl++;

	return x * x_3 + x_3 + x_2 + x + 1;
}

double f5 (double x)
{
	cl++;
	return exp(-x);
}

double f6 (double x)
{
	cl++;
	return 1 / (25 * x * x + 1);
}

