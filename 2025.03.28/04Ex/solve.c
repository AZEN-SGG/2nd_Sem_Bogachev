#include "solve.h"
#include "matrix.h"
#include <math.h>


void t4_solve(const double * restrict A, double * restrict x_0, const double * restrict b, double * restrict x, double * restrict r, int n, int m)
{

	for (int k = 0; k < m; ++k)
	{
		double *swap_temp = 0;
		double t = 0;
		double dot_Ar_r = 0, dot_Ar_Ar = 0;
		
		#pragma omp parallel for
		for (int i = 0; i < n; ++i)
		{
			double sum = 0;
			#pragma omp simd reduction(+:sum)
			for (int j = 0; j < n; ++j)
				sum += A[i*n + j] * x_0[j];
			r[i] = sum - b[i];
		}

		#pragma omp parallel for reduction(+:dot_Ar_r, dot_Ar_Ar)
		for (int i = 0; i < n; ++i)
		{
			double ri = r[i];
			double sum = 0;
			#pragma omp simd reduction(+:sum)
			for (int j = 0; j < n; ++j)
				sum += A[i*n + j] * r[j];
			
			dot_Ar_r += sum * ri;
			dot_Ar_Ar += sum * sum;
		}
		
		t = dot_Ar_r / dot_Ar_Ar;
		
		#pragma omp simd
		for (int i = 0; i < n; ++i)
			x[i] = x_0[i] - r[i]*t;
		
		swap_temp = x;
		x = x_0;
		x_0 = swap_temp;
	}

	if (m % 2 == 0) // Проверил 100 раз	
		#pragma omp simd
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

