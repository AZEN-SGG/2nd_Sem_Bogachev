#include "solve.h"

#include <math.h>
#include <float.h>

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

