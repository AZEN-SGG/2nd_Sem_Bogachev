#include "solve.h"

#include <float.h>
#include <math.h>
#include <stdio.h>

// the Newton interpolation polynomial
double t2_solve (const double x_0, const int n, const double * restrict X, double * restrict Y)
{
	double last_x = X[n-1];
	double last_y = Y[n-1];
	
	double value = 0;
	double start_value = 0;

	for (int k = 0; k < n-1; ++k)
	{
		printf ("------- K = %d -------\n", k);

		for (int i = n-2; i >= k; --i)
		{
			const double x_i = X[i-k];
			const double y_i = Y[i];
			
			if (fabs(last_x - x_i) < DBL_EPSILON)
				return DBL_MAX;
			
//			printf ("Y[%d] = (%lf - %lf) / (%lf - %lf)\n", i+1, last_y, y_i, last_x, x_i);
			Y[i+1] = (last_y - y_i) / (last_x - x_i);
			printf ("I = %d, f(x%d, ... , x%d) = %lf\n", i, i-k+1, i+2, Y[i]);

			last_x = x_i;
			last_y = y_i;
		}

		last_x = X[n-1];
		last_y = Y[n-1];
	}

	last_x = X[0];
	start_value = 1;
	value = Y[0];

	for (int i = 1; i < n; ++i)
	{
		start_value *= (x_0 - last_x);
		if (fabs(Y[i]) > DBL_EPSILON) 
			value += Y[i] * start_value;
		printf ("i = %d, start_value = %lf, value = %lf, last_x = %lf\n", i, start_value, value, last_x);
		printf ("Y[%d] = %lf\n", i, Y[i]);
		last_x = X[i];
	}

	return value;
}

