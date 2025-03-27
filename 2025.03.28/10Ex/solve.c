#include "solve.h"
#include "matrix.h"
#include <math.h>


void t10_solve(const double * restrict A, double * restrict x_0, const double * restrict b, double * restrict x, double * restrict r, double * restrict w, int n, int m, double t)
{
	for (int k = 0; k < m; ++k)
	{
		double *swap_temp = 0;
		
		#pragma omp parallel for
		for (int i = 0; i < n; ++i)
		{
			double sum = 0;
			#pragma omp simd reduction(+:sum)
			for (int j = 0; j < n; ++j)
				sum += A[i*n + j] * x_0[j];
			r[i] = (b[i] - sum) * t;
		}

		for (int i = 0; i < n; ++i)
		{
			double sum = r[i];
			double inai = 0;

			#pragma omp simd reduction(+:sum)
			for (int j = 0; j < i; ++j)
				sum -= A[i*n + j] * r[j];
			
			inai = 1./A[i*n + i];
			w[i] = inai;
			r[i] = sum * inai;
		}

		#pragma omp simd
		for (int i = 0; i < n; ++i)
			r[i] *= A[i*n + i];

		for (int i = n-1; i >= 0; --i)
		{
			double sum = r[i];
			
			#pragma omp simd reduction(+:sum)
			for (int j = n-1; j > i; --j)
				sum -= A[i*n + j] * r[j];

			r[i] = sum * w[i];
		}

		#pragma omp simd
		for (int i = 0; i < n; i++)
			x[i] = x_0[i] + r[i];
		
		swap_temp = x;
		x = x_0;
		x_0 = swap_temp;
	}

	if (m % 2 == 0) // Проверил 100 раз
	{
		#pragma omp simd
		for (int i = 0; i < n; i++)
		{	double temp = x[i]; x[i] = x_0[i]; x_0[i] = temp; }
	} else
	{	double * swap_temp = x; x = x_0; x_0 = swap_temp; }
}

