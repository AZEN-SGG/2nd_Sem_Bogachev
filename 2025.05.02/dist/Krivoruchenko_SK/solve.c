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
		c = a - ((a - b) / (y_a - y_b)) * y_a;
		y = f(c);
		
		memcpy(&bits, &y, sizeof(bits));
		sgn_c = (bits >> 63) & 1;
		
		if ((c - a < DBL_EPSILON) || (c - b > DBL_EPSILON))
			it = m+1;
		else if (fabs(y) - eps < DBL_EPSILON)
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

	if (fabs(y_a) - eps < DBL_EPSILON)
	{
		*x = a;
		return 1;
	} if (fabs(y_b) - eps < DBL_EPSILON)
	{
		*x = b;
		return 1;
	} if (fabs(fabs(y_b) - fabs(y_a)) < DBL_EPSILON)
	{
		*x = a;
		return -1;
	}

	for (it = 1; it <= m; ++it)
	{
		c = b - ((b - a) / (y_b - y_a)) * y_b;
		y = f(c);
		
		if (fabs(y) - eps < DBL_EPSILON)
			break;
		else if (fabs(y_a) - fabs(y_b) > DBL_EPSILON)
		{
			a = c;
			y_a = y;
		} else if (fabs(y_b) - fabs(y_a) > DBL_EPSILON)
		{
			b = c;
			y_b = y;
		} else
			it = m+1;
	}
	
	if (it > m)
		it = -1;
	
	*x = c;

	return it;
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
		double eps, int m, double *x
) {
	int it = 1;
	double x_l = 0, y_l = 0, c = a, y = f(a);

	if (fabs(b - a) < DBL_EPSILON)
	{
		*x = a;
		return 1;
	}

	for (double h = (b - a) * 0.1; fabs(h) > DBL_EPSILON; h *= -0.1)
	{
		do {
			if (it > m)
				break;

			it++;
			x_l = c;
			y_l = y;
			
			c += h;
			y = f(c);
		} while (((y - y_l) - eps) > DBL_EPSILON);
		
		if (it > m)
		{
			it = -1;
			break;
		}

		if ((c - b) > DBL_EPSILON)
		{
			x_l = b;
			y_l = f(b);
			break;
		} else if ((a - c) > DBL_EPSILON)
		{
			x_l = a;
			y_l = f(b);
			break;
		}
	}
	
	*x = x_l;

	return it;
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
