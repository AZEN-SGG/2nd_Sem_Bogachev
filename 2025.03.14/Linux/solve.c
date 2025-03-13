#include "solve.h"
#include <math.h>

#define eps 1e-9

int compare(const double a, const double b)
{
	if (a - b > eps) return 1;
	else if (b - a > eps) return -1;
	return 0;
}

double t1_solve(double *a, int n, int m)
{
	int i, j;
	double cur = 0, maximum = 0;
	if (n > 0)
		for (j = 0; j < m; j++) maximum += fabs(a[j]);
	for (i = 1; i < n; i++)
	{
		cur = 0;
		for (j = 0; j < m; j++)
			cur = fabs(a[i * m + j]);
		if (compare(cur, maximum) == 1) maximum = cur;
	}

	return maximum;
}

double t2_solve(double *a, int n, int m)
{
	int i, j;
	double cur = 0, maximum = 0;
	if (m > 0)
		for (i = 0; i < n; i++) maximum += fabs(a[i * m]);
	for (j = 1; j < m; j++)
	{
		cur = 0;
		for (i = 0; i < n; i++)
			cur += fabs(a[i * m + j]);
		if (compare(cur, maximum) == 1) maximum = cur;
	}

	return maximum;
}

double t3_solve(const double *A, const double *X, double *B, int m, int n)
{
	double r = 0;
	int i, j;
	for (i = 0; i < n; i++) B[i] = -B[i];

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			B[i] += A[i * m + j] * X[j];
		r += fabs(B[i]);
	}
	return r;
}

double t4_solve(const double *A, const double *X, double *B, int m, int n)
{
	double maximum = 0, cur;
	int i, j;

	for (i = 0; i < n; i++)
	{
		cur = -B[i];
		for (j = 0; j < m; j++)
			cur += A[i * m + j] * X[j];
		cur = fabs(cur);
		if (compare(cur, maximum) == 1) maximum = cur;
	}

	return maximum;
}

double t5_solve(const double *A, const double *b, int n, int m)
{
	double temp, summa, maximum = 0;
	int i, j, k;

	if (n <= 0 || m <= 0) return 0;

	for (i = 0; i < n; i++)
	{
		summa = 0;
		for (k = 0; k < n; k++) {
			temp = 0;
			for (j = 0; j < m; j++)
				temp += A[i * m + j] * b[j * n + k];

			if (k == i) temp--;
			summa += fabs(temp);
		}
		if (compare(summa, maximum) == 1) maximum = summa;		
	}

	return maximum;
}

double t6_solve(const double *A, const double *b, int n, int m)
{
	double temp, summa, maximum = 0;
	int i, j, k;

	if (n <= 0 || m <= 0) return 0;


	for (k = 0; k < n; k++) 
	{
		summa = 0;
		for (i = 0; i < n; i++)
		{
			temp = 0;
			for (j = 0; j < m; j++)
				temp += A[i * m + j] * b[j * n + k];

			if (k == i) temp--;
			summa += fabs(temp);
		}
		if (compare(summa, maximum) == 1) maximum = summa;		
	}

	return maximum;
}

double t7_solve(double *a, int n, int m)
{
	int i, j;
	double cur = 0, maximum = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			if (i == 0 || i == n-1 || j == 0 || j == m-1)
				if (compare(fabs(a[i*m + j]), maximum) == 1)
					maximum = fabs(a[i*m + j]);
	
	for (i = 1; i < n-1; i++)
		for (j = 1; j < m-1; j++)
		{
			cur = (a[(i-1)*m + j] + a[(i+1)*m + j] + a[i*m + (j-1)] + a[i*m + (j+1)]) / 5;
			if (compare(fabs(cur), maximum) == 1) maximum = fabs(cur);
			a[i*m + j] = cur;
		}

	return maximum;
}

double t8_solve(double *a, int n, int m)
{
	int i, j;
	double cur = 0, maximum = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			if (i == 0 || i == n-1 || j == 0 || j == m-1)
				if (compare(fabs(a[i*m + j]), maximum) == 1)
					maximum = fabs(a[i*m + j]);
	
	for (i = n-2; i > 0; i--)
		for (j = m-2; j > 0; j--)
		{
			cur = (a[(i+1)*m + j] + a[(i-1)*m + j] + a[i*m + (j-1)] + a[i*m + (j+1)]) / 5;
			if (compare(fabs(cur), maximum) == 1) maximum = fabs(cur);
			a[i*m + j] = cur;
		}

	return maximum;
}

double t9_solve(double *a, int n, int m)
{
	int i, j;
	double cur = 0, maximum = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			if (i == 0 || i == n-1 || j == 0 || j == m-1)
				if (compare(fabs(a[i*m + j]), maximum) == 1)
					maximum = fabs(a[i*m + j]);
	
	for (i = 1; i < n-1; i++)
		for (j = m-2; j > 0; j--)
		{
			cur = (a[(i-1)*m + j] + a[(i+1)*m + j] + a[i*m + (j-1)] + a[i*m + (j+1)]) / 5;
			if (compare(fabs(cur), maximum) == 1) maximum = fabs(cur);
			a[i*m + j] = cur;
		}

	return maximum;
}

double t10_solve(double *a, int n, int m)
{
	int i, j;
	double cur = 0, maximum = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			if (i == 0 || i == n-1 || j == 0 || j == m-1)
				if (compare(fabs(a[i*m + j]), maximum) == 1)
					maximum = fabs(a[i*m + j]);
	
	for (i = n-2; i > 0; i--)
		for (j = 1; j < m-1; j++)
		{
			cur = (a[(i+1)*m + j] + a[(i-1)*m + j] + a[i*m + (j-1)] + a[i*m + (j+1)]) / 5;
			if (compare(fabs(cur), maximum) == 1) maximum = fabs(cur);
			a[i*m + j] = cur;
		}

	return maximum;
}

double t11_solve(double *a, int n, int m)
{
	int i, j, max_i = 0, max_j = 0;
	double temp = 0, maximum = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			if (compare(fabs(a[i*m + j]), maximum) == 1)
			{
				maximum = fabs(a[i*m + j]);
				max_i = i;
				max_j = j;
			}
	if (max_i != 0)	
		for (j = 0; j < m; j++)
		{
			temp = a[max_i*m+j];
			a[max_i*m+j] = a[j];
			a[j] = temp;
		}
	if (max_j != 0)
		for (i = 0; i < n; i++)
		{
			temp = a[i*m + max_j];
			a[i*m + max_j] = a[i*m];
			a[i*m] = temp;
		}

	return maximum;
}
