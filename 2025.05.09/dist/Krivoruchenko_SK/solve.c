#include "solve.h"
#include "comp.h"

#include <math.h>
#include <float.h>

double t1_solve (
		double (*f) (double), 
		double x, double h 
) {
	if (h < NUM_FPE)
		return DBL_MAX;
	return (f(x + h) - f(x)) / h;
}

// -------

double t2_solve (
		double (*f) (double), 
		double x, double h 
) {
	if (h < NUM_FPE)
		return DBL_MAX;
	return (f(x + h) - f(x - h)) / (2 * h);
}

// -------

double t3_solve (
		double (*f) (double), 
		double x, double h 
) {
	double h_2 = h * h;
	if (h_2 < NUM_FPE)
		return DBL_MAX;
	return (f(x + h) - 2 * f(x) + f(x - h)) / h_2;
}

// -------

double t4_solve (
		double (*f) (double), 
		double a, double b,
		int n	
) {
	const double h = (b - a) / n;
	double x = a;
	double sum = (f(a) + f(b)) * 0.5;

	if (h < NUM_FPE)
		return DBL_MAX;
	
	for (int i = 1; i < (n - 1); ++i)
	{
		x += h;
		sum += f(x);
	}

	return h * sum;
}

// -------

double t5_solve (
		double (*f) (double), 
		double a, double b,
		int n	
) {
	const double h = (b - a) / (2 * n);
	double x = a;
	double sum = (f(a) + f(b)) * 0.5;

	if (h < NUM_FPE)
		return DBL_MAX;
	
	for (int i = 1; i < (2 * n - 1); ++i)
	{
		x += h;
		sum += ((i & 1) + 1) * f(x);
	}

	return (b - a) * sum / (3 * n);
}

// -------

double t6_solve (
		double (*f) (double), 
		double a, double b,
		int n	
) {
	const double h = (b - a) / n;
	double x = a;
	double sum;

	if (is_null(a) || is_null(b))
		return DBL_MAX;

	f_global = f;
       	sum = (wf(a) + wf(b)) * 0.5;

	if (h < NUM_FPE)
		return DBL_MAX;
	
	for (int i = 1; i < (n - 1); ++i)
	{
		x += h;
		if (is_null(x))
			return DBL_MAX;
		sum += wf(x);
	}

	return h * sum;
}

// -------

double t7_solve (
		double (*f) (double), 
		double a, double b,
		int n	
) {
	const double h = (b - a) / (2 * n);
	double x = a;
	double sum;

	if (is_null(a) || is_null(b))
		return DBL_MAX;

	f_global = f;
       	sum = (wf(a) + wf(b)) * 0.5;

	if (h < NUM_FPE)
		return DBL_MAX;
	
	for (int i = 1; i < (2 * n - 1); ++i)
	{
		x += h;
		if (is_null(x))
			return DBL_MAX;
		sum += ((i & 1) + 1) * wf(x);
	}

	return (b - a) * sum / (3 * n);
}

// -------

