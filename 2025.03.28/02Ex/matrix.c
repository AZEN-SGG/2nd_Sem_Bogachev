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

