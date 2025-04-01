#include <stdio.h>
#include <string.h>
#include <omp.h>
#include "array_io.h"

io_status read_matrix(double *a, int n, const char *name)
{
	int i, j;
	FILE *fp;
	if (!(fp = fopen(name, "r"))) return ERROR_OPEN;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (fscanf(fp, "%lf", a + i * n + j) != 1) 
				{fclose(fp); return ERROR_READ;}
	fclose(fp);
	return SUCCESS;
}

void print_matrix(const double *a, int n, int p)
{
	int np = (n > p ? p : n);
	int i, j;

	for (i = 0; i < np; i++)
	{
		for (j = 0; j < np; j++)
			printf(" %10.3e", a[i * n + j]);
		printf("\n");
	}
}

void init_matrix(double *a, int n, int k)
{
	double (*q)(int, int, int, int);
	double (*f[])(int, int, int, int) = {f1, f2, f3, f4};
	int i, j;
	q = f[k-1];
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			a[i * n + j] = q(n, n, i+1, j+1);
}

void init_identity_matrix(double *a, int n)
{
	a = memset(a, 0, n * n * sizeof(double));
	
	#pragma omp simd
	for (int i = 0; i < n; ++i)
		a[i*n + i] = 1.0;
}
