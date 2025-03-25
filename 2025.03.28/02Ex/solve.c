#include "solve.h"
#include "matrix.h"
#include <math.h>


void t2_solve(const double * restrict A, double * restrict x_0, const double * restrict b, double * restrict x, int n, int m, double t)
{
	#pragma omp parallel for
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

	if (m % 2 == 0)	
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

double t2_get_r1(const double * restrict A, const double * restrict x_k, const double * restrict b, int n)
{
	double norm_r1x_1 = 0;
	double residual_norm_1 = 0;
	double r1 = 0;

	#pragma omp parallel for reduction(+:residual_norm_1, norm_r1x_1)
	for (int i = 0; i < n; ++i)
	{
		double bi = b[i];
		double sum = 0;
		
		#pragma omp simd reduction(+:sum)
		for (int j = 0; j < n; ++j)
			sum += A[i*n + j] * x_k[j];
		
		residual_norm_1 += fabs(sum - bi);
		norm_r1x_1 += fabs(bi);
	}

	r1 = residual_norm_1 / norm_r1x_1;

	return r1;
}

double t2_get_r2_value(const double * restrict x_k, int n)
{
	double r2 = 0;
	double abs_xi = 0;
	double abs_i = 0;

	#pragma omp parallel for reduction(+:abs_xi, abs_i)
	for (int i = 0; i < n; ++i)
	{
		short int modi = i ^ 1;
		abs_xi += fabs(x_k[i] - modi);
		abs_i += modi;
	}

	r2 = abs_xi / abs_i;
	return r2;
}
