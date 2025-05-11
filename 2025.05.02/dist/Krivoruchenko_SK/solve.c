#include "solve.h"

#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

int t1_solve (
		double (*f) (double), 
		double a, double b, 
		double eps, int m, double *x
) {
	int it = 0;
	uint64_t bits;
	double c = DBL_MAX, y, y_a = f(a), y_b = f(b);
	bool sgn_a, sgn_b, sgn_c;

	memcpy(&bits, &y_a, sizeof(bits));
	sgn_a = (bits >> 63) & 1;
	memcpy(&bits, &y_b, sizeof(bits));
	sgn_b = (bits >> 63) & 1;

	if (fabs(y_a) - eps < DBL_EPSILON)
	{
		*x = a;
		return 1;
	} if (fabs(y_b) - eps < DBL_EPSILON)
	{
		*x = b;
		return 1;
	}

	if (sgn_a == sgn_b)
	{
		*x = DBL_MAX;
		return -1;
	}
	
	for (it = 1; it <= m; ++it)
	{
		c = (a + b) * 0.5;
		y = f(c);
		
		memcpy(&bits, &y, sizeof(bits));
		sgn_c = (bits >> 63) & 1;
		
		if (fabs(y) - eps < DBL_EPSILON)
			break;
		else if ((fabs(c - a) < DBL_EPSILON) || (fabs(c - b) < DBL_EPSILON))
			it = m+1;
		else if (sgn_c == sgn_a)
		{
			a = c;
			y_a = y;
		} else if (sgn_c == sgn_b)
		{
			b = c;
			y_b = y;
		}
	}
	
	if (it > m)
		it = -1;
	
	*x = c;

	return it;
}

int t2_solve (
		double (*f) (double), 
		double (*d) (double), 
		double x_0, double eps, 
		int m, double *x
) {
	int it = 0;

	for (it = 1; it <= m; ++it)
	{	
		double y = f(x_0);
		double dy = d(x_0);

		if (fabs(y) - eps < DBL_EPSILON)
			break;
		
		if (fabs(dy) < DBL_EPSILON)
		{
			it = -1;
			break;
		}

		x_0 -= (y / dy);
	}

	if (it > m)
		it = -1;
	
	*x = x_0;
	return it;
}

int t3_solve (
		double (*f) (double), 
		double a, double b, 
		double eps, int m, double *x
) {
	int it = 0;
	uint64_t bits;
	double c = DBL_MAX, y, y_a = f(a), y_b = f(b);
	bool sgn_a, sgn_b, sgn_c;

	memcpy(&bits, &y_a, sizeof(bits));
	sgn_a = (bits >> 63) & 1;
	memcpy(&bits, &y_b, sizeof(bits));
	sgn_b = (bits >> 63) & 1;

	if (is_eps(y_a, eps))
	{
		*x = a;
		return 1;
	} else if (is_eps(y_b, eps))
	{
		*x = b;
		return 1;
	}

	if (sgn_a == sgn_b)
	{
		*x = DBL_MAX;
		return -1;
	}
	
	for (it = 1; it <= m; ++it)
	{
		c = a - ((b - a) / (y_b - y_a)) * y_a;
		y = f(c);
		
		memcpy(&bits, &y, sizeof(bits));
		sgn_c = (bits >> 63) & 1;
		
		if (is_eps(y, eps))
			break;
		else if (sgn_c == sgn_a)
		{	
			a = c;
			y_a = y;
		} else if (sgn_c == sgn_b)
		{
			b = c;
			y_b = y;
		}
	}
	
	if (it > m)
		it = -1;
	
	*x = c;

	return it;
}

int t4_solve (
		double (*f) (double), 
		double a, double b, 
		double eps, int m, double *x
) {
	int it = 0;
	double c = DBL_MAX, y, y_a = f(a), y_b = f(b);

	if (is_eps(y_a, eps))
	{
		*x = a;
		return 1;
	} if (is_eps(y_b, eps))
	{
		*x = b;
		return 1;
	} if (is_equal(fabs(y_b), fabs(y_a)))
	{
		*x = a;
		return -1;
	}

	for (it = 1; it <= m; ++it)
	{
		// c = b - ((b - a) / (y_b - y_a)) * y_b;
		c = a - ((b - a) / (y_b - y_a)) * y_a;
		y = f(c);
		
		if (is_eps(y, eps))
			break;
		else if (fabs(y_a) - fabs(y_b) > DBL_EPSILON)
		{
			a = c;
			y_a = y;
		} else 
		{
			b = c;
			y_b = y;
		} 
		
		if (is_equal(y_a, y_b))
			it = m+1;
	}
	
	if (it > m)
		it = -1;
	
	*x = c;

	return it;
}

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

int t6_solve (
		double (*f) (double), 
		const int m, double *d,
		double a, double b, 
		const double eps, const int M, double *res
) {
	const int len = m + 1;
	
	double *y_lst = d;
	double *x_lst = d + len;
	double *t_lst = d + (len << 1);

	int it;

	if (is_eps(y_lst[0], eps)) {
		*res = a;
		return 1;
	} else if (is_eps(y_lst[m], eps)) {
		*res = b;
		return 1;
	}

	for (it = 1; it <= M; ++it)
	{
		double maximum = 0;
		int max_i = 0;

		double x = construct_poly(0, len, y_lst, x_lst);
		double y = f(x);

		if (is_eps(y, eps))
		{
			*res = x;
			return it;
		}

		// Возвращение значений функции в x_lst можно было встроить в суммирование полинома, но мало толку
		for (int i = 0; i < len; ++i)
		{
			double xi = t_lst[i];
			double yi = y_lst[i];

			x_lst[i] = xi;

			if (is_equal(y, yi))
				return -1;
			
			if ((yi - maximum) > DBL_EPSILON) {
				maximum = yi;
				max_i = i;
			}
		}
		
		y_lst[max_i] = y;
		x_lst[max_i] = x;
		t_lst[max_i] = x;
	}

	return -1;
}

int t7_solve (
		double (*f) (double), 
		double x_0, double eps, 
		int m, double *x
) {
	int it = 0;
	double y = f(x_0);

	if (fabs(y - x_0) - eps < DBL_EPSILON)
	{
		*x = x_0;
		return 1;
	}

	for (it = 1; it <= m; ++it)
	{
		x_0 = y;
		y = f(x_0);
		
		if (fabs(y - x_0) - eps < DBL_EPSILON)
			break;
	}

	if (it > m)
		it = -1;
	
	*x = x_0;

	return it;
}

int t8_solve (
		double (*f) (double), 
		double a, double b, 
		double eps, int m, double *res
) {
	int it = 1;
	double h = a - b;
	double x_l = 0, y_l = 0, x = a, y = f(a);

	if (fabs(b - a) < DBL_EPSILON)
	{
		*res = a;
		return 1;
	}

	while (it <= m)
	{
		h *= -0.1;

		while (1)
		{
			it++;

			if (it > m)
				return -1;

			x_l = x;
			y_l = y;

			x += h;
			y = f(x);
			if ((y_l - y) > DBL_EPSILON)
				break;

			if ((a - x) > DBL_EPSILON || (x - b) > DBL_EPSILON) {
				*res = x_l;
				return it;
			}

		}

		if ((y_l - y) < eps) {
			*res = x_l;
			return it;
		}
	}

	return -1;
}

int t9_solve (
		double (*f) (double), 
		double a, double b, 
		double eps, int m, double *x
) {
	const double gdrt = 2 / (1 + sqrt(5));
	int it = 0;

	double x_1 = b + (a - b) * gdrt, x_2 = a + (b - a) * gdrt;
	double y_1 = f(x_1), y_2 = f(x_2);

	for (it = 1; it <= m; ++it)
	{
		if (y_1 - y_2 > DBL_EPSILON)
		{
			b = x_2;

			x_2 = x_1;
			y_2 = y_1;

			x_1 = b + (a - b) * gdrt;
			y_1 = f(x_1);
		} else
		{
			a = x_1;

			x_1 = x_2;
			y_1 = y_2;

			x_2 = a + (b - a) * gdrt;
			y_2 = f(x_2);
		}

		if (fabs(b - a) < eps)
		{
			*x = x_1;
			break;
		}
	}

	if (it > m)
		it = -1;

	return it;
}
