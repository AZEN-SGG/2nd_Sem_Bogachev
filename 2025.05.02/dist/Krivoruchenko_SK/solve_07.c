#include "solve_07.h"

#include <math.h>
#include <float.h>

int t7_solve (
		double (*f) (double), 
		double x_0, double eps, 
		int m, double *x
) {
	int it = 0;

	for (it = 1; it <= m; ++it)
	{
		const double y = f(x_0);
		const double max = fabs((y < x_0) ? x_0 : y);
		
		if (fabs(y - x_0) < eps * max) {
			x_0 = y;
			break;
		}
		
		x_0 = y;
	}

	if (it > m)
		it = -1;
	
	*x = x_0;

	return it;
}

