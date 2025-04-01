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

double get_r1(const int n, const double * restrict A, const double * restrict X)
{
	double maximum = 0;

	if (n > 4000) return 0;
	
	#pragma omp parallel for reduction(max:maximum)
	for (int j = 0; j < n; ++j)
	{
		double sum = 0;
		
		#pragma omp simd reduction(+:sum)
		for (int i = 0; i < n; ++i)
		{
			int in = i*n;
			double sum_ij = - (i == j);

			#pragma omp simd reduction(+:sum_ij)
			for (int k = 0; k < n; ++k)
				sum_ij += A[in + k] * X[k*n + j];
			
			sum += fabs(sum_ij);
		}

		if (maximum < sum)
			maximum = sum;
	}

	return maximum;
}

double get_r2(const int n, const double * restrict A, const double * restrict X)
{
	double maximum = 0;

	if (n > 4000) return 0;
	
	#pragma omp parallel for reduction(max:maximum)
	for (int j = 0; j < n; ++j)
	{
		double sum = 0;

		#pragma omp simd reduction(+:sum)
		for (int i = 0; i < n; ++i)
		{
			int in = i*n;
			double sum_ij = - (i == j);

			#pragma omp simd reduction(+:sum_ij)
			for (int k = 0; k < n; ++k)
				sum_ij += X[in + k] * A[k*n + j];
			
			sum += fabs(sum_ij);
		}

		if (maximum < sum)
			maximum = sum;
	}

	return maximum;
}

