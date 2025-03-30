#include "solve.h"
#include "io_status.h"
#include <float.h>

// c - changes in rows
int t14_solve(int n, double * restrict A, double * restrict X, int * restrict c)
{
	for (int k = 0; k < n; ++k) {
		int kn = 0, maxn = 0
		max_t max = { .val = -1.0 };	
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

		#pragma omp parallel for
		for (int j = 0; j < n; ++j)
		{
			double swap = X[k*n + j];
			X[k*n + j] = X[max.i*n + j];
			X[max.i*n + j] = swap;
				
			if (j >= k)
			{
				swap = A[k*n + j];
				A[k*n + j] = A[max.i*n + j];
				A[max.i*n + j] = swap;
			}
		}

		#pragma omp parallel for
		for (int i = 0; i < n; ++i)
		{
			double swap = X[i*n + k];
			X[i*n + k] = X[i*n + max.j];
			X[i*n + max.j] = swap;
				
			if (i >= k)
			{
				swap = A[i*n + k];
				A[i*n + k] = A[i*n + max.j];
				A[i*n + max.j] = swap;
			}
		}	
	}
}
