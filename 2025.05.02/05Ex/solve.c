#include "solve.h"

#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

int t5_solve (
		double (*f) (double), 
		double a, double b, 
		double eps, int m, double *x
) {
	int it;
	double c = (a + b) * 0.5;

	double y_a = f(a);
	double y_c = f(c);
	double y_b = f(b);
	
	if (is_null(y_a))
	{
		*x = a;
		return 1;
	} else if (is_null(y_b))
	{
		*x = b;
		return 1;
	} else if (is_null(y_c))
	{
		*x = c;
		return 1;
	}

	if (is_equal(a, b))
		return -1;
	else if (is_equal(a, c))
	       return -1;
	else if (is_equal(b, c))
		return -1;

	for (it = 1; it < m+1; ++it)
	{
		double *temp_pnt = 0, *inner_max_pnt;
		const double angle = (c - a) / (y_c - y_a);
		const double x_new = a - 
			angle * y_a +
		       	((((b - c) / (y_b - y_c)) - angle) / (y_b - y_a)) * y_a * y_c;
		const double y_new = f(x_new);

		if (is_eps(y_new, eps))
		{
			*x = x_new;
			return it;
		}

		if (
			is_equal(x_new, a) ||
			is_equal(x_new, c) ||
			is_equal(x_new, b)
		   )
			return -1;

		inner_max_pnt = fp_abs_max(&c, &b, &y_c, &y_b, &temp_pnt);	
		*fp_abs_max(&a, inner_max_pnt, &y_a, temp_pnt, &temp_pnt) = x_new;
		*temp_pnt = y_new;
	}

	if (it > m)
		return -2;
	else
	{
		double temp = 0, *temp_x_pnt = fpmax(&c, &b, -y_c, -y_b, &temp);
		*x = *fpmax(&a, temp_x_pnt, -y_a, temp, &temp);
		return it;
	}
}

