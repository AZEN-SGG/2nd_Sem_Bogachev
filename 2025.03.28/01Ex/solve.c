#include "solve.h"
#include <math.h>


double t1_solve(double * restrict A, double * restrict x_0, double * restrict x, int n, int m)
{
	for (int i = 0; i < m; ++i)
	{
		double * swap_temp;
		matvec_mul(n, A, x_0, x);
		
		swap_temp = x;
		x = x_0;
		x_0 = swap_temp;
	}

	if (m % 2 == 0)
	{	
		for (int i = 0; i < n; i++)
		{
			double temp = x[i];
			x[i] = x_0[i];
			x_0[i] = temp;
		}
	} else
	{
		double * swap_temp = x;
		x = x_0;
		x_0 = swap_temp;
	}

	return t1_get_eigenvalue_approx(A, x, x_0, n);
}

void matvec_mul(int n, double * restrict A, double * restrict x, double * restrict x_k)
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

double t1_get_eigenvalue_approx(double * restrict A, double * restrict x_k, double * restrict x, int n)
{
	double dot_Ax_x = 0;
	double dot_x_x = 0;
	double rayleigh_quotient = 0;
	
	#pragma omp parallel for reduction(+:dot_Ax_x, dot_x_x)
	for (int i = 0; i < n; i++)
	{
		double x_i = x_k[i];
		double sum = 0;
		#pragma omp simd reduction(+:sum)
		for (int j = 0; j < n; j++)
			sum += A[i * n + j] * x_k[j];
		x[i] = sum;
		dot_Ax_x += sum * x_i;
		dot_x_x += x_i * x_i;
	}

	rayleigh_quotient = dot_Ax_x / dot_x_x;

	return rayleigh_quotient;
}

double t1_get_residual_norm(double * restrict x_k, double * restrict x, int n, double r1)
{
	double norm_r1x_1 = 0;
	double residual_norm_1 = 0;
	double relative_residual = 0;

	#pragma omp parallel for reduction(+:residual_norm_1, norm_r1x_1)
	for (int i = 0; i < n; ++i)
	{
		double rx = r1 * x_k[i];
		residual_norm_1 += fabs(x[i] - rx);
		norm_r1x_1 += fabs(rx);
	}

	relative_residual = residual_norm_1 / norm_r1x_1;

	return relative_residual;
}

