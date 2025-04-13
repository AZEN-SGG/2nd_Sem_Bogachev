#include "solve.h"
#include "io_status.h"
#include "array_io.h"
#include "matrix.h"
#include <float.h>
#include <math.h>

#define EPS 1.2e-16

// Прямой ход Гауса
void gauss_inverse(const int n, const int k, double * restrict A, double * restrict X)
{
	const double inv_akk = 1./A[k*n + k];
	
	for (int j = 0; j < k+1; ++j)
		X[k*n + j] *= inv_akk;

	for (int j = k+1; j < n; ++j)
	{
		A[k*n + j] *= inv_akk;
		X[k*n + j] *= inv_akk;
	}
	
	for (int i = k+1; i < n; ++i)
	{
		const double aik = A[i*n + k];
		
		for (int j = 0; j < k+1; ++j)
			X[i*n + j] -= X[k*n + j] * aik;

		for (int j = k+1; j < n; ++j)
		{
			A[i*n + j] -= A[k*n + j] * aik;
			X[i*n + j] -= X[k*n + j] * aik;
		}
	}
}

// Обратный ход метода Гаусса
void gauss_back_substitution(const int n, double * restrict A, double * restrict X)
{
	// Идём с последней строки и вычитаем её из последующих
	for (int k = n-1; k > 0; --k)
		for (int i = 0; i < k; ++i)
		{
			const double aik = A[i*n + k];

			for (int j = 0; j < n; ++j)
				X[i*n + j] -= X[k*n + j] * aik;	
		}
}

// c - changes in rows
int t14_solve(int n, double * restrict A, double * restrict X, int * restrict c)
{
	double norm = get_matrix_norm(n, A);
	double eps = EPS*norm;

	// Проходимся по главным минорам
	for (int k = 0; k < n; ++k) {
		double maximum = -1.;
		int max_i = 0, max_j = 0;
		
		// Ищем максимальный элемент минора
		for (int i = k; i < n; ++i)
			for (int j = k; j < n; ++j)
				if (fabs(A[i*n + j]) > maximum) {
					maximum = fabs(A[i*n + j]);
					max_i = i;
					max_j = j;
				}
			
		// Если максимальный по модулю элемент равен нулю, значит матрица вырождена
		if (fabs(maximum) <= eps)
			return SINGULAR;
		
		// Меняем строки местами, если максимум находится не в k строке
		if (max_i != k)
		{
			for (int j = 0; j < k; ++j)
			{
				double swap = X[k*n + j];
				X[k*n + j] = X[max_i*n + j];
				X[max_i*n + j] = swap;
			}
	
			for (int j = k; j < n; ++j)
			{
				double swap = X[k*n + j];
				X[k*n + j] = X[max_i*n + j];
				X[max_i*n + j] = swap;
				
				swap = A[k*n + j];
				A[k*n + j] = A[max_i*n + j];
				A[max_i*n + j] = swap;
			}
		}

		// Меняем столбцы местами
		if (max_j != k)
		{
			int swap_temp = c[max_j];
			c[max_j] = c[k];
			c[k] = swap_temp;

			for (int i = 0; i < n; i++)
			{
				double swap = A[i*n + k];
				A[i*n + k] = A[i*n + max_j];
				A[i*n + max_j] = swap;
			}
		}
		
		gauss_inverse(n, k, A, X);
	}

	gauss_back_substitution(n, A, X);

	for (int k = 0; k < n; ++k)
	{
		const int kn = k*n;	
		int i = c[k];
		
		while (i != k)
		{
			const int in = i*n;
			const int swap_int = c[i];
			c[i] = i;
			i = swap_int;

			for (int j = 0; j < n; ++j)
			{
				double swap_temp = X[in+j];
				X[in+j] = X[kn+j];
				X[kn+j] = swap_temp;
			}
		}
	}

	return 0;
}



