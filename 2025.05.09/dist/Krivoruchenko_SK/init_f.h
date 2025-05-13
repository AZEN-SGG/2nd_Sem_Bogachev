#ifndef INIT_F_H
#define INIT_F_H

#include <math.h>

static inline double weight (double x)
{
	return 1. / sqrt(fabs(x));
}

// ------------------------------------

static int cl = 0;

static inline int get_call_count (void) 
{
	return cl;
}

static inline double f0 (double x)
{
	cl++;
	(void)x;

	return 1;
}

static inline double f1 (double x)
{
	cl++;
	return x + 1;
}

static inline double f2 (double x)
{
	double x_2 = x * x;
	cl++;
	return x_2 + x + 1;
}

static inline double f3 (double x)
{
	double x_2 = x * x;
	double x_3 = x_2 * x;
	cl++;

	return x_3 + x_2 + x + 1;
}

static inline double f4 (double x)
{
	double x_2 = x * x;
	double x_3 = x_2 * x;
	double x_4 = x_3 * x;
	cl++;

	return x_4 + x_3 + x_2 + x + 1;
}

static inline double f5 (double x)
{
	cl++;
	return exp(-x);
}

static inline double f6 (double x)
{
	double x_2 = x * x;
	cl++;
	return 1 / (25 * x_2 + 1);
}

// ------------------------------------

#endif
