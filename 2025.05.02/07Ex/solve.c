#include "solve.h"

#include <math.h>
#include <float.h>

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

