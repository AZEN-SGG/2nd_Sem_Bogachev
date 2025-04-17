#include "solve.h"

#include <float.h>
#include <math.h>
#include <stdio.h>

// Newton's interpolation polynomial with derivative
double t4_solve (
		const double x_0, const int n, 
		const double * restrict X, 
		double * restrict Y,
		double * restrict D
		)
{
	double value, start_value;
	double x_j = X[n-1];
	double y_j = Y[n-1];

	for (int i = n-2; i >= 0; --i)
	{
		const double x_i = X[i];
		const double y_i = Y[i];
		
		if (fabs(x_j - x_i) < DBL_EPSILON)
			return DBL_MAX;
		
		Y[i+1] = (y_j - y_i) / (x_j - x_i);
		printf ("I = %d, f(x%d, ... , x%d) = %lf\n", i, i+1, i+2, Y[i+1]);

		y_j = y_i;
		x_j = x_i;
	}

	for (int i = 1; i < n; ++i)
		printf ("f(x%d, x%d) = %lf\n", i-1, i, Y[i]);

	for (int k = 1; k < n-1; ++k)
	{
		double f_j = D[n-1];

		printf ("------- K = %d -------\n", k);
		
		for (int l = n*2-2; l > k*2; --l)
		{
			const int i = l >> 1;
			double x_i, f_i, *f;

			if (l & 1)
			{
				x_i = X[i-k];

				f_i = D[i];
				f = Y + i + 1;
			} else 
			{
				x_j = X[i];
				x_i = X[i-k];

				f_i = Y[i];
				f = D + i;
			}

			if (fabs(x_j - x_i) < DBL_EPSILON)
				return DBL_MAX;
			
			*f = (f_j - f_i) / (x_j - x_i);
//			printf ("f(x%d, x%d, ..., x%d) = %lf\n", i-k, i-k, i+1, Y[i+1]);
//			printf ("f(x%d, ..., x%d, x%d) = %lf\n", i-k, i+1, i+1, D[i+1]);
			
			f_j = f_i;	
			
//			printf ("I = %d, f(x%d, ... , x%d) = %lf\n", i, i-k+1, i+2, Y[i+1]);
		}

		printf("------- Y -------\n");
		for (int i = 0; i < n; ++i)
			printf("Y[%d] = %lf\n", i, Y[i]);

		printf("------- D -------\n");
		for (int i = 0; i < n; ++i)
			printf("D[%d] = %lf\n", i, D[i]);
	}

	start_value = 1;
	value = 0;

	printf("------- Y -------\n");
	for (int i = 0; i < n; ++i)
		printf("Y[%d] = %lf\n", i, Y[i]);

	printf("------- D -------\n");
	for (int i = 0; i < n; ++i)
		printf("D[%d] = %lf\n", i, D[i]);

	for (int i = 0; i < n; ++i)
	{
		const double diff = (x_0 - X[i]);
		value += Y[i] * start_value;
		start_value *= diff;
		value += D[i] * start_value;
		start_value *= diff;
	}

	return value;
}

