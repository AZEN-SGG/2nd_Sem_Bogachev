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
	double c = (a + b) / 2;

	double y_a = f(a);
	double y_c = f(c);
	double y_b = f(b);
	
	if (is_null(y_a))
		return 1;
	else if (is_null(y_b))
		return 1;
	else if (is_null(y_c))
		return 1;

	if (is_equal(a, b))
		return -1;
	else if (is_equal(a, c))
	       return -1;
	else if (is_equal(b, c))
		return -1;

	for (it = 1; it < m+1; ++it)
	{
		double x_new, y_new, *temp_pnt = 0, *inner_max_pnt;
		const double m_1 = (y_c - y_a) / (c - a);
		const double m_2 = (y_b - y_c) / (b - c);

		const double A = (m_2 - m_1) / (b - a);
		const double B = m_1 - A * (a + c);
		const double C = y_a - a * m_1 + A * a * c;
		
		const double D = B * B - 4 * A * C;

		if (is_null(A))
			return -3;
		else if (D < -DBL_EPSILON)
			return -1;
		else if (D > DBL_EPSILON)
		{
			const double sqrt_D = sqrt(D);
			const double inv_A = 1./(2 * A);

			double x_1 = (-B + sqrt_D) * inv_A;
			double x_2 = (-B - sqrt_D) * inv_A;

			double y_x_1 = f(x_1);
			double y_x_2 = f(x_2);

			if (is_eps(y_x_1, eps))
			{
				*x = x_1;
				return it;
			} else if (is_eps(y_x_2, eps))
			{
				*x = x_2;
				return it;
			} else if (y_x_2 - y_x_1 > DBL_EPSILON)
			{
				x_new = x_1;
				y_new = y_x_1;
			} else
			{
				x_new = x_2;
				y_new = y_x_2;
			}
		} else
		{
			double x_1 = -B / (2 * A);
			double y_x_1 = f(x_1);

			if (is_eps(y_x_1, eps))
			{
				*x = x_1;
				return it;
			}

			x_new = x_1;
			y_new = y_x_1;
		}

		if (
			is_equal(x_new, a) ||
			is_equal(x_new, c) ||
			is_equal(x_new, b)
		   )
			return -1;

		inner_max_pnt = fp_abs_max(&c, &b, &y_c, &y_b, &temp_pnt);	
		*fp_abs_max(&a, inner_max_pnt, &y_a, temp_pnt, &temp_pnt) = x_new;
		if (fabs(y_new) - fabs(*temp_pnt) > DBL_EPSILON)
			return -4;
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

