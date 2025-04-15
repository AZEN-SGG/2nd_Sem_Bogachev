#include "solve.h"
#include "io_status.h"
#include "array_io.h"
#include "matrix.h"
#include <float.h>
#include <math.h>

#define EPS 1.2e-16

// c - changes in rows
int t14_solve(int n, double * restrict A, double * restrict X, int * restrict c)
{
	double norm = get_matrix_norm(n, A);
	double eps = EPS*norm;

	double maximum = -1.;
	int max_i = 0, max_j = 0;

	// Ищем максимальный элемент минора
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		{
			const double aij = fabs(A[i*n + j]);
			if (aij > maximum) {
				maximum = aij;
				max_i = i;
				max_j = j;
			}
		}
	
	// Проходимся по главным минорам
	for (int k = 0; k < n; ++k) 
	{			
		double inv_akk;

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
		
		// Прямой ход метода Гаусса
		inv_akk = 1./A[k*n + k];
	
		for (int j = 0; j < k+1; ++j)
			X[k*n + j] *= inv_akk;

		for (int j = k+1; j < n; ++j)
		{
			A[k*n + j] *= inv_akk;
			X[k*n + j] *= inv_akk;
		}
	
		maximum = -1.;
		for (int i = k+1; i < n; ++i)
		{
			const double aik = A[i*n + k];
			
			for (int j = 0; j < k+1; ++j)
				X[i*n + j] -= X[k*n + j] * aik;

			for (int j = k+1; j < n; ++j)
			{
				const double aij = A[i*n + j] - A[k*n + j] * aik;
				if (fabs(aij) > maximum)
				{
					maximum = fabs(aij);
					max_i = i;
					max_j = j;
				}
				
				A[i*n + j] = aij;
				X[i*n + j] -= X[k*n + j] * aik;
			}
		}
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

