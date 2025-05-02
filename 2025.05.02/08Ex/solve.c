#include "solve.h"

#include <math.h>
#include <float.h>
#include <stdbool.h>


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

