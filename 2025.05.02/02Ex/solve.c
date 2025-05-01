#include "solve.h"

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

		if (y - eps < DBL_EPSILON)
			break;
		
		if (fabs(dy) < DBL_EPSILON)
		{
			it = m+1;
			break;
		}

		x_0 -= (y / dy);
	}
	
	*x = x_0;
	return it;
}

