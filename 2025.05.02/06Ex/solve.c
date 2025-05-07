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



int t6_solve (
		double (*f) (double), 
		const int m, double *d
		double a, double b, 
		const double eps, const int M, double *x
) {
	const int len = m + 1;

	double *y_lst = d;
	double *x_lst = d + len;
	double *t_lst = d + (len << 1);
	
	double last_x = a;
	double last_y = f(a);
	const int h = (b - a) / m;
	
	y_lst[0] = last_y;
	x_lst[0] = last_x;
	t_lst[0] = last_x;

	for  (int i = 1, double t_x = a ; i < len ; i++, t_x += h)
	{
		double t_y = f(t_x);

		y_lst[i] = t_y;
		x_lst[i] = t_x;

		
	}

}
