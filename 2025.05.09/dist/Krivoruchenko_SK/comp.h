#ifndef COMP_H
#define COMP_H

#include <float.h>
#include <math.h>

static inline double * fpmax (double *pa, double *pb, double fa, double fb, double *max_f_p)
{
	if ((fa - fb) > DBL_EPSILON) 
	{
		*max_f_p = fa;
		return pa;
	} else
	{
		*max_f_p = fb;
		return pb;
	}
}

static inline double * fp_abs_max (double *pa, double *pb, double *fa, double *fb, double **max_f_p)
{
	if ((fabs(*fa) - fabs(*fb)) > DBL_EPSILON) 
	{
		*max_f_p = fa;
		return pa;
	} else
	{
		*max_f_p = fb;
		return pb;
	}
}

static inline int is_equal (const double a, const double b)
{
	double diff = a - b;
	double max_val = (a > b) ? a : b;
	return ((diff < 0) ? -diff : diff) < (DBL_EPSILON * max_val);
}

static inline int is_null (const double a)
{
	return ((a < 0) ? -a : a) < DBL_EPSILON;
}

static inline int is_eps (const double a, const double eps)
{
	return ((a < 0) ? -a : a) < eps;
}

#endif
