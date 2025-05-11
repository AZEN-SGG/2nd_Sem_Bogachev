#include "init_f.h"

#include <math.h>
#include <float.h>


static int cl = 0;
static int cl_d = 0;

int get_call_count (void) 
{
	return cl;
}

int get_call_function_count (void)
{
	return cl;
}

int get_call_derivative_count (void)
{
	return cl_d;
}

double f0 (double x)
{
	cl++;
	(void)x;

	return 1;
}

double d0 (double x)
{
	cl_d++;
	(void)x;

	return 0;
}

double f1 (double x)
{
	cl++;
	return (x * 1e-100) - 1.0;
}

double d1 (double x)
{
	(void)x;
	cl_d++;
	return 1;
}

double f2 (double x)
{
	double x_2 = x * x;
	cl++;
	return 4 - x_2;
}

double d2 (double x)
{
	cl_d++;
	return -2 * x;
}

double f3 (double x)
{
	double x_2 = x * x;
	double x_3 = x * x_2;
	cl++;

	return x_3 + 3 * x_2 + 16;
}

double d3 (double x)
{
	cl_d++;

	return 3 * x * x + 6 * x;
}

double f4 (double x)
{
	double x_2 = x * x;
	double x_4 = x_2 * x_2;
	cl++;

	return 3 - 2 * x_2 - x_4;
}

double d4 (double x)
{
	cl_d++;

	return -4 * x - 4 * ((x * x) * x);
}

double f5 (double x)
{
	double sq_x = sqrt(fabs(x) + 1);
	cl++;
	return sq_x - 2;
}

double d5 (double x)
{
	cl_d++;
	if (x < -DBL_EPSILON)
		return (-1.0 / (sqrt(fabs(x) + 1))) * 0.5;
	else if (x > DBL_EPSILON)
		return (1.0 / (sqrt(fabs(x) + 1))) * 0.5;
	return 0;
}

double f6 (double x)
{
	double sq_x = sqrt(fabs(x) + 1);
	double sq = sqrt(sq_x + 1);
	cl++;
	return sq - 2;
}

double d6 (double x)
{
	double sqrt_x = sqrt(fabs(x) + 1);
	cl_d++;
	
	if (x < -DBL_EPSILON)
		return (-1.0 / (sqrt(sqrt_x + 1) * sqrt_x)) * 0.25;
	else if (x > DBL_EPSILON)
		return (1.0 / (sqrt(sqrt_x + 1) * sqrt_x)) * 0.25;
	return 0;
}
