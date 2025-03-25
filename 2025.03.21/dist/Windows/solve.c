#include "solve.h"
#include <math.h>
#include <float.h>
#include <stdio.h>

#define eps 1e-17

int t1_solve(double *a, int m, int n)
{
	int l, min_j = 0, del_j;
	double minimum = (m * n > 0) ? DBL_MAX : 0;

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			double temp = fabs(a[i*n + j]);
			if (temp < minimum) 
			{ 
				minimum = temp; 
				min_j = j; 
			}
		}

	for (l = min_j+1, del_j = 1; l < m*n; l++)
	{
		if (l == ((n * del_j) + min_j))
			del_j++;
		else 
			a[l - del_j] = a[l];
	}

	return min_j + 1;
}

int t2_solve(double *a, int m, int n)
{
	int min_i = 0, min_j = 0;
	double minimum = (m * n > 0) ? fabs(a[0]) : 0;

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if ((minimum - fabs(a[i*n + j])) > eps) { minimum = fabs(a[i*n + j]); min_i = i; min_j = j; }

	for (int l = min_j+1, del_j = 1; l < min_i*n; l++)
	{
		if (l == ((n * del_j) + min_j))
			del_j++;
		else 
			a[l - del_j] = a[l];
	}

	for (int l = (min_i+1)*n, del_j = min_i; l < m*n; l++)
	{
		if (l == ((n * (del_j + 1)) + min_j))
			del_j++;
		else 
			a[l - del_j - n] = a[l];
	}

	return min_i * n + min_j;
}

int t3_solve(double *a, int m, int n)
{
	int min_j = 0;
	double minimum = -1;

	for (int j = 0; j < n; j++)
	{
		double cur = 0;
		for (int i = 0; i < m; i++)
			cur += fabs(a[i*n + j]);	
		if ((minimum - cur) > eps || j == 0) { minimum = cur; min_j = j; }
	}

	for (int l = min_j+1, del_j = 1; l < m*n; l++)
	{
		if (l == ((n * del_j) + min_j))
			del_j++;
		else 
			a[l - del_j] = a[l];
	}

	return min_j + 1;
}

int t4_solve(double *a, int m, int n)
{
	int min_i = 0, min_j = 0;
	double minimum = -1;

	for (int i = 0; i < m; i++)
	{
		double sum = 0;
		for (int j = 0; j < n; j++)
			sum += fabs(a[i*n + j]);

		if ((minimum - sum) > eps || i == 0) { minimum = sum; min_i = i; }
	}

	for (int j = 0; j < n; j++)
	{
		double sum = 0;
		for (int i = 0; i < m; i++)
			sum += fabs(a[i*n + j]);

		if ((minimum - sum) > eps || j == 0) { minimum = sum; min_j = j; }
	}

	for (int l = min_j+1, del_j = 1; l < min_i*n; l++)
	{
		if (l == ((n * del_j) + min_j))
			del_j++;
		else 
			a[l - del_j] = a[l];
	}

	for (int l = (min_i+1)*n, del_j = min_i; l < m*n; l++)
	{
		if (l == ((n * (del_j + 1)) + min_j))
			del_j++;
		else 
			a[l - del_j - n] = a[l];
	}

	return min_i * n + min_j;
}

int t5_solve(double *a, int m, int n)
{
	int max_j = 0;
	double maximum = 0;

	for (int j = 0; j < n; j++)
	{
		double sum = 0;
		for (int i = 0; i < m; i++)
			if (i != j)
				sum += fabs(a[i*n + j]);
		
		if ((sum - maximum) > DBL_EPSILON * fmax(fabs(maximum), fabs(sum))) { maximum = sum; max_j = j; }
	}

	for (int l = max_j+1, del_j = 1; l < m*n; l++)
	{
		if (l == ((n * del_j) + max_j))
			del_j++;
		else 
			a[l - del_j] = a[l];
	}

	return max_j + 1;
}

int t6_solve(double *a, int m, int n)
{
	int max_j = 0, mn = (n < m) ? n : m;
	double maximum = 0;

	for (int j = 0; j < mn; j++)
	{
		double sum = 0;
		for (int i = 0; i < m; i++)
			if (i != j)
				sum += fabs(a[i*n + j] - a[j*n + j]);

		if ((sum - maximum) > eps) { maximum = sum; max_j = j; }
	}

	for (int l = max_j+1, del_j = 1; l < m*n; l++)
	{
		if (l == ((n * del_j) + max_j))
			del_j++;
		else 
			a[l - del_j] = a[l];
	}

	return max_j + 1;
}

int t7_solve(double *a, int m, int n)
{
	int min_j = 0;
	double minimum = 0;
	double inm = 1./m;

	for (int j = 0; j < n; j++)
	{
		double sum = 0;
		double avg = 0;
		for (int k = 0; k < m; k++) avg += a[k*n + j];
		avg *= inm;

		for (int i = 0; i < m; i++)
		{
			double temp = (a[i*n + j] - avg);
	       		sum += temp * temp;
		}	

		if ((minimum - sum) > eps || j == 0) { minimum = sum; min_j = j; }
	}

	for (int l = min_j+1, del_j = 1; l < m*n; l++)
	{
		if (l == ((n * del_j) + min_j))
			del_j++;
		else 
			a[l - del_j] = a[l];
	}

	return min_j + 1;
}

int t8_solve(double *a, int m, int n)
{
	const int BS = 30;
	int max_i = 0, max_j = 0;
	double maximum = 0;
	
	for (int jj = 0; jj < n; jj += BS)
		for (int j = jj; j < jj + BS && j < n; j++)
			{
				double sum_j = 0;
				for (int ii = 0; ii < m; ii += BS) 
					for (int k = ii; k < ii + BS && k < m; k++)
						sum_j += fabs(a[k*n + j]);
			
				for (int ii = 0; ii < m; ii += BS) 
					for (int i = ii; i < ii + BS && i < m; i++)
					{
						double sum_i = 0;
						double aij = fabs(a[i*n + j]);
						sum_j -= aij;

						if (j == 0)
						{
							double num = a[i*n];
							for (int kk = 1; kk < n; kk += BS)
								for (int k = kk; k < kk + BS && k < n; k++)
									sum_i += fabs(a[i*n + k]);

							a[i*n] = copysign(fabs(num) + sum_i, num);
						}
						else
							sum_i = fabs(a[i*n]) - fabs(a[i*n + j]);
	
						if (((sum_j + sum_i) - maximum) > eps)
							maximum = (sum_j + sum_i), max_i = i, max_j = j;
			
						sum_j += aij;
					}
			}

	if (max_j != 0)
		for (int ii = 0; ii < m; ii += BS)
			for (int i = ii; i < ii + BS && i < m; i++)
			{
				double orig = a[i*n];
				double num = fabs(orig);
				
				for (int jj = 1; jj < n; jj += BS)
					for (int j = jj; j < jj + BS && j < n; j++)
						num -= fabs(a[i*n + j]);

				a[i*n] = copysign(num, orig);
			}

	for (int l = max_j+1, del_j = 1; l < max_i*n; l++)
	{
		if (l == ((n * del_j) + max_j))
			del_j++;
		else 
			a[l - del_j] = a[l];
	}

	for (int l = (max_i+1)*n, del_j = max_i; l < m*n; l++)
	{
		if (l == ((n * (del_j + 1)) + max_j))
			del_j++;
		else 
			a[l - del_j - n] = a[l];
	}

	return max_i * n + max_j;
}

int t9_solve(double *a, int m, int n)
{
	const int BS = 32;
	int max_i = 0, max_j = 0;
	double maximum = 0;

	for (int jj = 0; jj < n; jj += BS)
		for (int ii = 0; ii < m; ii += BS)
			for (int j = jj; j < jj + BS && j < n; j++)
				for (int i = ii; i < ii + BS && i < m; i++)
				{
					double sum_i = 0;
					double sum_j = 0;
					double aij = a[i*n + j];
				
					for (int kk = 0; kk < n; kk += BS)
						for (int k = kk; k < kk + BS && k < n; k++) if (k != j)
							sum_i += fabs(a[i*n + k] - aij);
			
					for (int kk = 0; kk < m; kk += BS)
						for (int k = kk; k < kk + BS && k < m; k++) if (i != k)
							sum_j += fabs(a[k*n + j] - aij);
			
					if (((sum_j + sum_i) - maximum) > eps)
						maximum = (sum_j + sum_i), max_i = i, max_j = j;
				}

	for (int l = max_j+1, del_j = 1; l < max_i*n; l++)
	{
		if (l == ((n * del_j) + max_j))
			del_j++;
		else 
			a[l - del_j] = a[l];
	}

	for (int l = (max_i+1)*n, del_j = max_i; l < m*n; l++)
	{
		if (l == ((n * (del_j + 1)) + max_j))
			del_j++;
		else 
			a[l - del_j - n] = a[l];
	}

	return max_i * n + max_j;
}

int t10_solve(double *a, int m, int n)
{
	const int BS = 30;
	int min_i = 0, min_j = 0;
	double minimum = (m*n > 0) ? DBL_MAX : 0;
	double inn = 1./n, inm = 1./m;

	for (int ii = 0; ii < m; ii += BS)
	for (int i = ii; i < ii + BS && i < m; i++)
	{
		double cur = 0;
		double sum = 0;
		double sq_sum = 0;
		for (int jj = 0; jj < n; jj += BS)
		for (int j = jj; j < jj + BS && j < n; j++)
		{	
			double temp = a[i*n + j];
			sum += temp;
			sq_sum += temp * temp;
		}

		cur = sq_sum - (sum * sum) * inn;
		if ((minimum - cur) > DBL_EPSILON * fmax(fabs(minimum), fabs(cur))) {
			minimum = cur;
			min_i = i;
		}
	}

	minimum = (m*n > 0) ? DBL_MAX : 0;

	for (int jj = 0; jj < n; jj += BS)
	for (int j = jj; j < jj + BS && j < n; j++)
	{
		double cur = 0;
		double sum = 0;
		double sq_sum = 0;

		for (int ii = 0; ii < m; ii += BS)
			for (int i = ii; i < ii + BS && i < m; i++)
			{
				double temp = a[i*n + j];
				sum += temp;
				sq_sum += temp * temp;
			}

		cur = sq_sum - (sum * sum) * inm;
		if ((minimum - cur) > DBL_EPSILON * fmax(fabs(minimum), fabs(cur))) {
			minimum = cur;
			min_j = j;
		}
	}
	
	for (int l = min_j+1, del_j = 1; l < min_i*n; l++)
	{
		if (l == ((n * del_j) + min_j))
			del_j++;
		else 
			a[l - del_j] = a[l];
	}

	for (int l = (min_i+1)*n, del_j = min_i; l < m*n; l++)
	{
		if (l == ((n * (del_j + 1)) + min_j))
			del_j++;
		else 
			a[l - del_j - n] = a[l];
	}

	return min_i * n + min_j;
}
