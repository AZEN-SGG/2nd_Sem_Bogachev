#include "solve.h"
#include "io_status.h"
#include <float.h>
#include <math.h>
#include "array_io.h"
#include "matrix.h"
#include <stdio.h>

// c - changes in rows
int t14_solve(int n, double * restrict A, double * restrict X, int * restrict c)
{
	double norm = get_matrix_norm(n, A);

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


		// Если максимальный по модулю элемент равен нулю, значит матрица вырождена
		if (fabs(maximum) < DBL_EPSILON * norm)
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
		
		gauss_inverse(n, k, A, X);
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
	
	for (int i = k+1; i < n; ++i)
	{
		const int in = i*n;
		const double aik = A[in + k];
		A[in + k] = 0;
		X[in + k] -= X[kk] * aik;
		
		for (int j = 0; j < k; ++j)
			X[in + j] -= X[kn + j] * aik;
		
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

		for (int i = 0; i < k; ++i)
		{
			const int in = i*n;
			const double aik = A[in + k];
			A[in + k] = 0;

			for (int j = 0; j < n; ++j)
				X[in + j] -= X[kn + j] * aik;	
		}
	}
}

