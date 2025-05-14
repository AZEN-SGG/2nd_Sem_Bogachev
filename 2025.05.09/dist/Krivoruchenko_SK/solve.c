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

int t8_solve (
		double (*f) (double), 
		double a, double b,
		double eps, double *res
) {
	int it;

	double n = 1;
	double h = (b - a);
	double integ_n = (f(a) + f(b)) * h*0.5;

	for (it = 1; it <= MAX_ITER; ++it)
	{
		double x = a + h*0.5;
		double integ_2n = 0;
	
		for (int i = 0; i < n; i++)
		{
			integ_2n += f(x);
			x += h;
		}

		h *= 0.5;
		integ_2n = integ_2n * h + integ_n * 0.5;

		if (fabs(integ_2n - integ_n) < eps)
			break;
		
		integ_n = integ_2n;
		n *= 2;
	}

	if (it > MAX_ITER) 
		return -1;
	
	*res = integ_n;

	return n;
}

// -------

int t9_solve (
		double (*f) (double), 
		double a, double b,
		double eps, double *res
) {
	int it;
	double integ_n;

	int n = 2;
	double h = (b - a) * 0.5;
	double s1 = (f(a) + f(b)) * h/3;
	double s2 = f(a + h) * h*4/3;

	for (it = 1; it <= MAX_ITER; ++it)
	{
		double x = a + h*0.5;
		double s2_2n = 0;

		for (int i = 0; i < n; i++)
		{
			s2_2n += f(x);
			x += h;
		}

		s2_2n *= h*2/3;

		if (fabs((s2_2n - s1 * 0.5) - s2 * 0.75) < eps) {
			integ_n = s1 + s2;
			break;
		}
		
		s1 = s1 * 0.5 + s2 * 0.25;
		s2 = s2_2n;

		h *= 0.5;
		n <<= 1;
	}

	if (it > MAX_ITER) 
		return -1;
	
	*res = integ_n;

	return n;
}

// -------

double t10_solve (
		double (*f) (double), 
		double a, double eps, 
		double *res
) {
	int it;

	int h = 1;
	double b = a;
	double integ = 0;

	for (it = 1; it <= MAX_ITER; ++it)
	{
		int n;
		double ipart = 0;
		b += h;
		
		n = t8_solve(f, a, b, eps, &ipart);
		if (n < 0)
			return -2;

		integ += ipart;
		
		if (fabs(ipart) < eps)
			break;

		a = b;
		h <<= 1;
	}

	if (it > MAX_ITER) 
		return -1;
	
	*res = integ;

	return b;
}

// -------

double t11_solve (
		double (*f) (double), 
		double a, double eps, 
		double *res
) {
	int it;

	int h = 1;
	double b = a;
	double integ = 0;

	for (it = 1; it <= MAX_ITER; ++it)
	{
		int n;
		double ipart = 0;
		b += h;
		
		n = t9_solve(f, a, b, eps, &ipart);
		if (n < 0)
			return -2;

		integ += ipart;
		
		if (fabs(ipart) < eps)
			break;

		a = b;
		h <<= 1;
	}

	if (it > MAX_ITER) 
		return -1;
	
	*res = integ;

	return b;
}

// -------
