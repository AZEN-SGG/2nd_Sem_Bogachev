#include "solve.h"
#include <math.h>

#define eps 1e-6

int t1_solve(double *a, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = i; j < n; j++)
			if (i != j)
				if (fabs(a[i * n + j] - a[j * n + i]) > eps) return 0;
	return 1;
}

double t2_solve(double *a, int n)
{
	double trace = 0;
	int i;
	for (i = 0; i < n; i++)
		trace += a[i * n + i];
	return trace;
}

void t3_solve(double *a, int n)
{
	double temp;
	int i, j;
	for (i = 0; i < n; i++)
		for (j = i; j < n; j++)
			if (i != j) {
				temp = a[i * n + j];
				a[i * n + j] = a[j * n + i];
				a[j * n + i] = temp;
			}		
}

void t4_solve(double *a, int n)
{
	double temp;
	int i, j;
	for (i = 0; i < n; i++)
		for (j = i; j < n; j++)
			if (i != j) {
				temp = a[i * n + j];
				a[i * n + j] = (a[j * n + i] + temp) / 2;
				a[j * n + i] = (a[j * n + i] + temp) / 2;
			}		
}

void t5_solve(double *a, int n)
{
	double temp;
	int i, j;
	for (i = 0; i < n; i++)
		for (j = i; j < n; j++)
			if (i != j) {
				temp = a[i * n + j];
				a[i * n + j] = (temp - a[j * n + i]) / 2;
				a[j * n + i] = (a[j * n + i] - temp) / 2;
			} else a[i * n + j] = 0;
}

void t6_solve(double *a, int n, int m, int i, int j)
{
	double temp;
	int k;
	(void)n;
	for (k = 0; k < m; k++)
	{
		temp = a[i * m + k];
		a[i * m + k] = a[j * m + k];
		a[j * m + k] = temp;
	}
}

void t7_solve(double *a, int n, int m, int i, int j)
{
	double temp;
	int k;
	for (k = 0; k < n; k++)
	{
		temp = a[k * m + i];
		a[k * m + i] = a[k * m + j];
		a[k * m + j] = temp;
	}
}

void t8_solve(double *a, int n, int m, int i, int j, double g)
{
	int k;
	(void)n;
	for (k = 0; k < m; k++)
		a[j * m + k] += a[i * m + k] * g;
}

void t9_solve(const double *A, const double *b, double *c, int n, int m)
{
	matrix_multiply(A, b, c, n, m, 1);
}

void matrix_multiply(const double *A, const double *B, double *c, int n, int m, int l)
{
	int i, j, k, index;
	for (i = 0; i < n; i++)
		for (j = 0; j < l; j++)
		{
			index = i * l + j;
			c[index] = 0;
			for (k = 0; k < m; k++)
				c[index] += A[i * m + k] * B[k * l + j];
		}
}
