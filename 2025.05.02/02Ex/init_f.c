#include "init_f.h"

#include <math.h>


static int cl_f = 0;
static int cl_d = 0;

int get_call_function_count (void) 
{
	return cl_f;
}

int get_call_derivative_count (void)
{
	return cl_d;
}

double f0 (double x)
{
	cl_f++;
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
	cl_f++;
	return ((x * 1e-100) - 1.0) * 1e100;
}

double d1 (double x)
{
	cl_d++;
	return x;
}

double f2 (double x)
{
	cl_f++;
	return 4 - x * x;
}

double d2 (double x)
{
	cl_d++;
	return - 2 * x;
}

double f3 (double x)
{
	double x_2 = x * x;
	cl_f++;

	return x * x_2 + 3 * x_2 + 16;
}

double d3 (double x)
{
	cl_d++;

	return 3 * x * x + 6 * x;
}

double f4 (double x)
{
	double x_2 = x * x;
	cl_f++;

	return 3 - 2 * x_2 - x_2 * x_2;
}

double d4 (double x)
{
	cl_d++;

	return -4 * x - 4 * ((x * x) * x);
}

double f5 (double x)
{
	cl_f++;
	return sqrt(fabs(x) + 1) - 2;
}

double d5 (double x)
{
	cl_d++;
	return (((signbit(x)) ? -1 : 1) * (1.0 / (sqrt(fabs(x) + 1)))) * 0.5;
}

double f6 (double x)
{
	cl_f++;
	return sqrt(sqrt(fabs(x) + 1) + 1) - 2;
}

double d6 (double x)
{
	double sqrt_x = sqrt(fabs(x) + 1);
	cl_d++;
	
	return (((signbit(x)) ? -1 : 1) * (1.0 / (sqrt(sqrt_x + 1) * sqrt_x))) * 0.25;
}
