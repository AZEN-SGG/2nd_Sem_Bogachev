#include "solve.h"

#include <math.h>
#include <float.h>

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

