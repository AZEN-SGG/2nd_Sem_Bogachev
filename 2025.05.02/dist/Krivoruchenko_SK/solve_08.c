#include "solve_08.h"

#include <math.h>
#include <float.h>

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
