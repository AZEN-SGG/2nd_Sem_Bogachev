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
	return (x * 1e-100) - 1.0;
}

double f2 (double x)
{
	double x_2 = x * x;
	cl++;
	return 4 - x_2;
}

double f3 (double x)
{
	double x_2 = x * x;
	double x_3 = x * x_2;
	cl++;

	return x_3 + 3 * x_2 + 16;
}

double f4 (double x)
{
	double x_2 = x * x;
	double x_4 = x_2 * x_2;
	cl++;

	return 3 - 2 * x_2 - x_4;
}

double f5 (double x)
{
	double sq_x = sqrt(fabs(x) + 1);
	cl++;
	return sq_x - 2;
}

double f6 (double x)
{
	double sq_x = sqrt(fabs(x) + 1);
	double sq = sqrt(sq_x + 1);
	cl++;
	return sq - 2;
}

