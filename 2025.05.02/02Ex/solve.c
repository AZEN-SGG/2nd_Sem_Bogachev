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
	double y = f(x_0);

	for (it = 1; it < m; ++it)
	{	
		if (y - eps < DBL_EPSILON)
			break;

		x_0 -= (y / d(x_0));
		y = f(x_0);
		
	}
	
	*x = x_0;

	return it;
}

