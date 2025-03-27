#include "solve.h"
#include "matrix.h"
#include <math.h>


void t2_solve(const double * restrict A, double * restrict x_0, const double * restrict b, double * restrict x, int n, int m, double t)
{
	for (int k = 0; k < m; ++k)
	{
		double * swap_temp;
		matvec_mul(n, A, x_0, x);
		
		#pragma omp simd
		for (int i = 0; i < n; ++i)
			x[i] = (b[i] - x[i]) * t + x_0[i];
		
		swap_temp = x;
		x = x_0;
		x_0 = swap_temp;
	}

	if (m % 2 == 0) // Проверил 100 раз	
		for (int i = 0; i < n; i++)
		{
			double temp = x[i];
			x[i] = x_0[i];
			x_0[i] = temp;
		}
	else
	{
		double * swap_temp = x;
		x = x_0;
		x_0 = swap_temp;
	}
}
