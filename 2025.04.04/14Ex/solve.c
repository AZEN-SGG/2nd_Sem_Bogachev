#include "solve.h"
#include "io_status.h"
#include <float.h>

// c - changes in rows
int t14_solve(int n, double * restrict A, double * restrict X, int * restrict c)
{
	for (int k = 0; k < n; ++k) {
		max_t max = { .val = -1.0 };
		
		#pragma omp parallel for reduction(+:max)	
		for (int i = k; i < n; ++i)
			for (int j = k; j < n; ++j)
			{
				double aij = fabs(A[i * n + j]);
				if (aij > max.val) {
					max.val = aij;
					max.i = i;
					max.j = j;
				}
			}

		if (fabs(max.val) < DBL_EPSILON)
			return SINGULAR;
		
		if (max.i != k)
		{
			#pragma omp simd
			for (int kn = k*n, in = max.i*n; kn < k*(n+1); ++kn, ++in)
			{
				double swap = X[kn];
				X[kn] = X[in];
				X[in] = swap;
			}		
	
			#pragma omp parallel for simd
			for (int kn = k*n+k, in = max.i*n+k; kn < (k+1)*n; ++kn, ++in)
			{
				double swap = X[kn];
				X[kn] = X[in];
				X[in] = swap;
				
				swap = A[kn];
				A[kn] = A[in];
				A[in] = swap;
			}
		}

		if (max.j != j)
		{
			int swap_temp = c[max.j];
			c[max.j] = k;
			c[k] = swap_temp;

			#pragma omp simd
			for (int in = k * n; in < n; in+=n)
			{
				double swap = A[in + k];
				A[in + k] = A[in + max.j];
				A[in + max.j] = swap;
			}
		}

		gauss_inverse(n, k, A, X);
		gauss_back_substitution(n, A, X);

		for (int k = 0; k < n; ++k)
		{
			int str
			while (
		}
	}
}

void gauss_inverse(const int n, const int k, double * restrict A, double * restrict X)
{
	const int kn = k*n, const int kk = kn + k;
	const double inv_akk = 1./A[kn + k];
	A[kn + k] = 1.;	
	
	for (int ij = kn; ij < kn+k; ++ij)
	{
		double xij = X[ij];
		if (fabs(xij) > DBL_EPSILON) X[ij] = xij*inv_akk;
	}

	for (int ij = kn + k+1; ij < kn+n; ++ij)
	{
		double aij = A[ij], xij = X[ij];
		if (fabs(aij) > DBL_EPSILON) A[ij] = aij*inv_akk;
		if (fabs(xij) > DBL_EPSILON) X[ij] = xij*inv_akk;
	}
	
	#pragma omp parallel for
	for (int i = k+1; i < n; ++i)
	{
		const int in = i*n;
		const double aik = A[in + k];
		A[in + k] = 0;
		X[in + k] -= X[kk] * aik;
		
		#pragma omp simd
		for (int j = 0; j < k; ++j)
			X[in + j] -= X[kn + j] * aik;
		
		#pragma omp simd
		for (int j = k+1; j < n; ++j)
		{
			A[in + j] -= A[kn + j] * aik;
			X[in + j] -= X[kn + j] * aik;
		}
	}
}

void gauss_back_substitution(const int n, double * restrict A, double * restrict X)
{
	for (int k = n-1; k > 0; --k)
	{
		const int kn = k * n;

		#pragma omp parallel for
		for (int i = 0; i < j; ++i)
		{
			const int in = i*n;
			const double aik = A[in + k];
			A[in + k] = 0;

			#pragma omp simd
			for (int j = 0; j < n; ++j)
				X[in + j] -= X[kn + j] * aik;	
		}
	}
}

