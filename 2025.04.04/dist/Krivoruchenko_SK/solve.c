#include "solve.h"
#include "io_status.h"
#include "array_io.h"
#include "matrix.h"
#include <float.h>
#include <math.h>
#include <stdio.h>

// c - changes in rows
int t14_solve(int n, double * restrict A, double * restrict X, int * restrict c)
{
	double norm = get_matrix_norm(n, A);
	double eps = DBL_EPSILON*norm;

	if (norm < DBL_EPSILON)
		return SINGULAR;

	// Проходимся по главным минорам
	for (int k = 0; k < n; ++k) {
		double maximum = -1.;
		int max_i = 0, max_j = 0;
		
		// Ищем максимальный элемент минора
		for (int i = k; i < n; ++i)
			for (int j = k; j < n; ++j)
			{
				double aij = fabs(A[i * n + j]);
				if (aij > maximum) {
					maximum = aij;
					max_i = i;
					max_j = j;
				}
			}
		
		printf("\n------- K = %d -------\n", k);
		printf("Maximum = %lf i = %d j = %d\n", maximum, max_i, max_j);

		// Если максимальный по модулю элемент равен нулю, значит матрица вырождена
		if (fabs(maximum) < eps)
			return SINGULAR;
		
		// Меняем строки местами, если максимум находится не в k строке
		if (max_i != k)
		{
			int kn = k*n;
			int in = max_i*n;

			for (int i = 0; i < k; ++i)
			{
				int kni = kn+i, ini = in+i;
				double swap = X[kni];
				X[kni] = X[ini];
				X[ini] = swap;
			}
	
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

		// Меняем столбцы местами
		if (max_j != k)
		{
			int swap_temp = c[max_j];
			c[max_j] = c[k];
			c[k] = swap_temp;

			for (int in = 0; in < n*n; in+=n)
			{
				double swap = A[in + k];
				A[in + k] = A[in + max_j];
				A[in + max_j] = swap;
			}
		}

		printf("BEFORE GAUSS\n");
		printf("Original matrix:\n");
		print_matrix(A, n, n);
		printf("Inverse matrix:\n");
		print_matrix(X, n, n);
		
		gauss_inverse(n, k, A, X);
		
		printf("AFTER GAUSS\n");
		printf("Original matrix:\n");
		print_matrix(A, n, n);
		printf("Inverse matrix:\n");
		print_matrix(X, n, n);
	}

	gauss_back_substitution(n, A, X);
	
	// Возвращаем строки назад
	for (int k = 0; k < n; ++k)
	{
		int pnt_cur = c[k];

		if (pnt_cur != k)
		{
			int pnt_nxt = 0;
		
			for (int j = 0; j < n; ++j)
			{
				int loc_cur = pnt_cur;
				double temp_cur = X[k*n + j];
				double temp_nxt = 0;

				do {
					temp_nxt = X[loc_cur*n + j];
					X[loc_cur*n + j] = temp_cur;
					temp_cur = temp_nxt;					

					loc_cur = c[loc_cur];
				} while (loc_cur != k);
	
				X[k*n + j] = temp_cur;
			}

			do {
				pnt_nxt = c[pnt_cur];
				c[pnt_cur] = pnt_cur;
				pnt_cur = pnt_nxt;
			} while (pnt_nxt != k);

			c[k] = k;
		}
	}

	return 0;
}
// Прямой ход Го ----- йда
void gauss_inverse(const int n, const int k, double * restrict A, double * restrict X)
{
	const int kn = k*n;
	const int kk = kn + k;
	const double inv_akk = 1./A[kk];
	A[kk] = 1.;	
	
	for (int ij = kk+1; ij < kn+n; ij++)
		A[ij] *= inv_akk;
	
	for (int ij = kn; ij <= kk; ij++)
		X[ij] *= inv_akk;
	
	for (int i = k+1; i < n; ++i)
	{
		const int in = i*n;
		const double aik = A[in + k];
		A[in + k] = 0;
		
		for (int ij = in, kj = kn; kj < kn + n; ij++, kj++)
			X[ij] -= X[kj] * aik;
		
		for (int ij = in+k+1, kj = kk+1; ij < in+n; ij++, kj++)
			A[ij] -= A[kj] * aik;
	}
}

// Обратный ход метода Гаусса
void gauss_back_substitution(const int n, double * restrict A, double * restrict X)
{
	// Идём с последней строки и вычитаем её из последующих
	for (int k = n-1; k > 0; --k)
	{
		const int kn = k * n;

		for (int i = 0; i < k; ++i)
		{
			const int in = i*n;
			const double aik = A[in + k];
			A[in + k] = 0;

			for (int j = 0; j < n; ++j)
				X[in + j] -= X[kn + j] * aik;	
		}

		printf("\n------- K = %d -------\n", k);
		printf("Original matrix:\n");
		print_matrix(A, n, n);
		printf("Inverse matrix:\n");
		print_matrix(X, n, n);
	}
}

