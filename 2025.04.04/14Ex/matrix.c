#include "matrix.h"
#include <math.h>

void init_vec_b(const double * restrict a, double * restrict b, int n)
{
	#pragma omp parallel for
	for (int i = 0; i < n; ++i)
	{
		double sum = 0;

		#pragma omp simd reduction(+:sum)
		for (int k = 0; k < n; k+=2)
			sum += a[i * n + k];

		b[i] = sum;
	}
}

void matvec_mul(int n, const double * restrict A, const double * restrict x, double * restrict x_k)
{
	#pragma	omp parallel for
	for (int i = 0; i < n; i++)
	{
		double sum = 0;
		#pragma omp simd reduction(+:sum)
		for (int j = 0; j < n; j++)
			sum += A[i * n + j] * x[j];
		x_k[i] = sum;
	}	
}

double get_r1(const double * restrict A, const double * restrict x_k, const double * restrict b, int n)
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

double get_r2_value(const double * restrict x_k, int n)
{
	double relative_error = 0;
	double total_diff = 0;
	double template_sum = 0;

	#pragma omp parallel for reduction(+:total_diff, template_sum)
	for (int i = 0; i < n; ++i)
	{
		short int modi = !(i & 1);
		total_diff += fabs(x_k[i] - modi);
		template_sum += modi;
	}

	relative_error = total_diff / template_sum;
	return relative_error;
}
