#include "solve.h"
#include "matrix.h"
#include <math.h>


double t1_solve(const double * restrict A, double * restrict x_0, double * restrict x, int n, int m)
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

double t1_get_eigenvalue_approx(const double * restrict A, double * restrict x_k, double * restrict x, int n)
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

void t3_solve(const double * restrict A, double * restrict x_0, const double * restrict b, double * restrict x, double * restrict r, int n, int m)
{

	for (int k = 0; k < m; ++k)
	{
		double *swap_temp = 0;
		double t = 0;
		double dot_r_r = 0, dot_Ar_r = 0;
		
		#pragma omp parallel for
		for (int i = 0; i < n; ++i)
		{
			double sum = 0;
			#pragma omp simd reduction(+:sum)
			for (int j = 0; j < n; ++j)
				sum += A[i*n + j] * x_0[j];
			r[i] = sum - b[i];
		}

		#pragma omp parallel for reduction(+:dot_r_r, dot_Ar_r)
		for (int i = 0; i < n; ++i)
		{
			double ri = r[i];
			double sum = 0;
			#pragma omp simd reduction(+:sum)
			for (int j = 0; j < n; ++j)
				sum += A[i*n + j] * r[j];
			
			dot_Ar_r += sum * ri;
			dot_r_r += ri * ri;
		}
		
		t = dot_r_r / dot_Ar_r;
		
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

void t5_solve(const double * restrict A, double * restrict x_0, const double * restrict b, double * restrict x, double * restrict r, int n, int m)
{
	for (int k = 0; k < m; ++k)
	{
		double *swap_temp = 0;
		double t = 0;
		double dot_Dr_r = 0, dot_ADr_Dr = 0;
		
		#pragma omp parallel for
		for (int i = 0; i < n; ++i)
		{
			double sum = 0;
			#pragma omp simd reduction(+:sum)
			for (int j = 0; j < n; ++j)
				sum += A[i*n + j] * x_0[j];
			r[i] = sum - b[i];
		}

		#pragma omp parallel for reduction(+:dot_Dr_r)
		for (int i = 0; i < n; ++i)
		{
			double d_ri = r[i] / A[i*n +i];
			dot_Dr_r += d_ri * r[i];
			r[i] = d_ri;
		}

		#pragma omp parallel for reduction(+:dot_ADr_Dr)
		for (int i = 0; i < n; ++i)
		{
			double sum = 0;

			#pragma omp simd reduction(+:sum)
			for (int j = 0; j < n; ++j)
				sum += A[i*n + j] * r[j];
			
			dot_ADr_Dr += sum * r[i];
		}
		
		t = dot_Dr_r / dot_ADr_Dr;

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

void t6_solve(const double * restrict A, double * restrict x_0, const double * restrict b, double * restrict x, double * restrict r, int n, int m)
{
	for (int k = 0; k < m; ++k)
	{
		double *swap_temp = 0;
		double t = 0;
		double dot_ADr_r = 0, dot_ADr_ADr = 0;
		
		#pragma omp parallel for
		for (int i = 0; i < n; ++i)
		{
			double sum = 0;
			#pragma omp simd reduction(+:sum)
			for (int j = 0; j < n; ++j)
				sum += A[i*n + j] * x_0[j];
			r[i] = (sum - b[i]) / A[i*n + i];
		}

		#pragma omp parallel for reduction(+:dot_ADr_r, dot_ADr_ADr)
		for (int i = 0; i < n; ++i)
		{
			double sum = 0;

			#pragma omp simd reduction(+:sum)
			for (int j = 0; j < n; ++j)
				sum += A[i*n + j] * r[j];
			
			dot_ADr_r += sum * r[i] * A[i*n + i];
			dot_ADr_ADr += sum * sum;
		}

		t = dot_ADr_r / dot_ADr_ADr;
		
		#pragma omp simd
		for (int i = 0; i < n; ++i)
			x[i] = x_0[i] - (r[i]*t);
		
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
				sum += A[i*n + j] * x_0[j];

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

void t9_solve(const double * restrict A, double * restrict x_0, const double * restrict b, double * restrict x, int n, int m, double t)
{
	for (int k = 0; k < m; ++k)
	{
		double * swap_temp;
		
		for (int i = n-1; i >= 0; --i)
		{
			double sum_x = 0;
			double sum_r = 0;
			double temp = 0;
			double aii = A[i*n + i];

			#pragma omp simd reduction(+:sum_x, sum_r)	
			for (int j = n-1; j > i; --j)
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
			for (int j = i-1; j >= 0; --j)
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
