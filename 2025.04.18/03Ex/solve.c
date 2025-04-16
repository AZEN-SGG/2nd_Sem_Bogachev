#include "solve.h"

#include <float.h>
#include <math.h>
#include <stdio.h>


// Interpolation polynomial according to Aitken's scheme
double t3_solve (const double x_0, const int n, const double * restrict X, double * restrict Y)
{
	for (int k = 0; k < n-1; ++k)
	{
		double x_j; 
		double y_j = Y[n-1];

//		printf ("------- K = %d -------\n", k);
		
		for (int i = n-2; i >= k; --i)
		{
			const double x_i = X[i-k];
			const double y_i = Y[i];
			x_j = X[i+1];
			
			if (fabs(x_j - x_i) < DBL_EPSILON)
				return DBL_MAX;
			
			Y[i+1] = ((x_0-x_i) * y_j - (x_0-x_j) * y_i) / (x_j - x_i);
//			printf ("I = %d, f(x%d, ... , x%d) = %lf\n", i, i-k+1, i+2, Y[i+1]);

			y_j = y_i;
		}
	}

	return Y[n-1];
}

