#include "solve_02.h"

#include <math.h>
#include <float.h>

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

