#include "solve.h"
#include "io_status.h"
#include <float.h>
#include <math.h>
#include "array_io.h"
#include <stdio.h>

// c - changes in rows
int t14_solve(int n, double * restrict A, double * restrict X, int * restrict c)
{
	// Проходимся по главным минорам
	for (int k = 0; k < n; ++k) {
		double maximum = -1.;
		int max_i = 0, max_j = 0;
		
		//printf("\n--------- K = %d ---------\n", k);
			
		// Ищем максимальный элемент минора
		#pragma omp parallel
		{
			double local_max = -1.;
			int loc_i = 0, loc_j = 0;

			#pragma omp for collapse(2) nowait	
			for (int i = k; i < n; ++i)
				for (int j = k; j < n; ++j)
				{
					double aij = fabs(A[i * n + j]);
					if (aij > local_max) {
						local_max = aij;
						loc_i = i;
						loc_j = j;
					}
				}
		
			#pragma omp critical
			{		
				if (local_max > maximum) {
					maximum = local_max;
					max_i = loc_i;
					max_j = loc_j;
				}
			}
		}


		// Если максимальный по модулю элемент равен нулю, значит матрица вырождена
		if (fabs(maximum) < DBL_EPSILON)
			return SINGULAR;
		
		//printf("Maximum = %lf for i = %d, j = %d\n", maximum, max_i, max_j);

		// Меняем строки местами, если максимум находится не в k строке
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

		//print_matrix(A, n, n);
		//printf("\n");

		// Меняем столбцы местами
		if (max_j != k)
		{
			int swap_temp = c[max_j];
			c[max_j] = c[k];
			c[k] = swap_temp;

			#pragma omp simd
			for (int in = k * n; in < n; in+=n)
			{
				double swap = A[in + k];
				A[in + k] = A[in + max_j];
				A[in + max_j] = swap;
			}
		}
		/*
		print_matrix(A, n, n);
		printf("\n");
		*/
		gauss_inverse(n, k, A, X);
		/*
		print_matrix(A, n, n);
		printf("Inverse matrix:\n");
		print_matrix(X, n, n);
		*/
	}

	gauss_back_substitution(n, A, X);
	
	// Возвращаем строки назад
	for (int k = 0; k < n; ++k)
	{
		int str_i = c[k];
		
		if (str_i != k)
			for (int j = 0; j < n; ++j)
			{
				int loc_k = k;
				int loc_i = str_i;
				double elem = X[k*n + j];
				
				do {
					X[loc_i*n + j] = elem;
					elem = X[loc_i*n + j];
					
					loc_k = loc_i;
					loc_i = c[loc_i];
					if (j == n-1)
						c[loc_k] = loc_k;
				} while (loc_i != k);
	
				X[k*n + j] = elem;
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
	
	for (int ij = kn; ij <= kn+k; ++ij)
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

// Обратный ход метода Гаусса
void gauss_back_substitution(const int n, double * restrict A, double * restrict X)
{
	// Идём с последней строки и вычитаем её из последующих
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

