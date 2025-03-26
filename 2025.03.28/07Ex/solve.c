#include "solve.h"
#include "matrix.h"
#include <math.h>


void t7_solve(const double * restrict A, double * restrict x_0, const double * restrict b, double * restrict x, double * restrict r, int n, int m, double t)
{
	(void)r;
	
	for (int k = 0; k < m; ++k)
	{
		double * swap_temp;

		#pragma omp parallel for
		for (int i = 0; i < n; ++i)
		{
			double sum = 0;
			
			#pragma omp simd reduction(+:sum)
			for (int j = 0; j < n; ++j)
				sum += A[i*n + j] * x[j];

			x[i] = x_0[i] + ((b[i] - sum) / A[i*n + i]) * t;
		}
	
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

