#include "solve.h"
#include "io_status.h"
#include <float.h>
#include <math.h>

// c - changes in rows
int t14_solve(int n, double * restrict A, double * restrict X, int * restrict c)
{
	for (int k = 0; k < n; ++k) {
		double maximum = -1.;
		int max_i = 0, max_j = 0;

		#pragma omp parallel for collapse(2) reduction(max:maximum)	
		for (int i = k; i < n; ++i)
			for (int j = k; j < n; ++j)
			{
				double aij = fabs(A[i * n + j]);
				#pragma omp critical
				{
					if (aij > maximum) {
						maximum = aij;
						max_i = i;
						max_j = j;
					}
				}
			}

		if (fabs(maximum) < DBL_EPSILON)
			return SINGULAR;
		
		if (max_i != k)
		{
			int kn = k*n;
			int in = max_i*n;

			#pragma omp simd
			for (int i = 0; i < k; ++i)
			{
				int kni = kn+i, ini = in+i;
				double swap = X[kni];
				X[kni] = X[ini];
				X[ini] = swap;
			}
	
			#pragma omp parallel for simd
			for (int i = k; i < n; ++i)
			{
				int kni = kn+i, ini = in+i;
				double swap = X[kni];
				X[kni] = X[ini];
				X[ini] = swap;
				
				swap = A[kni];
				A[kni] = A[ini];
				A[ini] = swap;
			}
		}

		if (max_j != k)
		{
			int swap_temp = c[max_j];
			c[max_j] = k;
			c[k] = swap_temp;

			#pragma omp simd
			for (int in = k * n; in < n; in+=n)
			{
				double swap = A[in + k];
				A[in + k] = A[in + max_j];
				A[in + max_j] = swap;
			}
		}

		gauss_inverse(n, k, A, X);
	}

	gauss_back_substitution(n, A, X);

	for (int k = 0; k < n; ++k)
	{
		int str_k = k;
		int str_i = c[k];
		
		if (str_i != k)
		{
			#pragma omp parallel for
			for (int j = 0; j < n; ++j)
			{
				double elem = X[k*n + j];
				
				do {
					X[str_i*n + j] = elem;
					elem = X[str_i*n + j];

					str_k = str_i;
					str_i = c[str_i];
					c[str_k] = str_k;
				} while (str_i != k);

				X[k*n + j] = elem;
			}
		}
	}

	return 0;
}

void gauss_inverse(const int n, const int k, double * restrict A, double * restrict X)
{
	const int kn = k*n;
	const int kk = kn + k;
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
		for (int i = 0; i < k; ++i)
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

