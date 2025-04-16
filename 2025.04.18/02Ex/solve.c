#include "solve.h"

#include <float.h>
#include <math.h>
#include <stdio.h>

// the Newton interpolation polynomial
double t2_solve (const double x_0, const int n, const double * restrict X, double * restrict Y)
{
	double value, start_value;

	for (int k = 0; k < n-1; ++k)
	{
		double last_x; 
		double last_y = Y[n-1];

//		printf ("------- K = %d -------\n", k);
		
		for (int i = n-2; i >= k; --i)
		{
			const double x_i = X[i-k];
			const double y_i = Y[i];
			last_x = X[i+1];
			
			if (fabs(last_x - x_i) < DBL_EPSILON)
				return DBL_MAX;
			
			Y[i+1] = (last_y - y_i) / (last_x - x_i);
//			printf ("I = %d, f(x%d, ... , x%d) = %lf\n", i, i-k+1, i+2, Y[i+1]);

			last_y = y_i;
		}
	}

	start_value = 1;
	value = 0;

	for (int i = 0; i < n; ++i)
	{
		value += Y[i] * start_value;
		start_value *= (x_0 - X[i]);
	}

	return value;
}

