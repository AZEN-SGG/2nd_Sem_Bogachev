#include "solve.h"
#include "matrix.h"
#include <math.h>


void t8_solve(const double * restrict A, double * restrict x_0, const double * restrict b, double * restrict x, double * restrict r, double * restrict w, int n, int m, double t)
{
	(void)r;
	(void)w;
	
	for (int k = 0; k < m; ++k)
	{
		double * swap_temp;
		
		for (int i = 0; i < n; ++i)
		{
			double sum_x = 0;
			double sum_r = 0;
			double temp = 0;
			double aii = A[i*n + i];

			#pragma omp simd reduction(+:sum_x, sum_r)	
			for (int j = 0; j < i; ++j)
			{
				double aij = A[i*n + j];
				double rj = aij * x_0[j];
			       	sum_x += rj - aij * x[j];
				sum_r += rj;
			}

			temp = aii * x_0[i];	
			sum_x += temp;
			sum_r += temp;

			#pragma omp simd reduction(+:sum_r)	
			for (int j = i+1; j < n; ++j)
				sum_r += A[i*n + j] * x_0[j];

			x[i] = (sum_x + (b[i] - sum_r) * t) / aii;
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

