#include "solve.h"
#include "comp.h"

#include <math.h>
#include <float.h>

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
		c = b - ((b - a) / (y_b - y_a)) * y_b;
		y = f(c);
		
		if (is_eps(y, eps))
			break;
		else if (fabs(y_a) - fabs(y_b) > DBL_EPSILON)
		{
			a = c;
			y_a = y;
		} else 
		// if (fabs(y_b) - fabs(y_a) > DBL_EPSILON)
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

