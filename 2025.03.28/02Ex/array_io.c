#include <stdio.h>
#include "array_io.h"

io_status read_matrix(double *a, int m, int n, const char *name)
{
	int i, j;
	FILE *fp;
	if (!(fp = fopen(name, "r"))) return ERROR_OPEN;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			if (fscanf(fp, "%lf", a + i * n + j) != 1) 
				{fclose(fp); return ERROR_READ;}
	fclose(fp);
	return SUCCESS;
}

void print_matrix(const double *a, int m, int n, int p)
{
	int mp = (m > p ? p : m);
	int np = (n > p ? p : n);
	int i, j;

	for (i = 0; i < mp; i++)
	{
		for (j = 0; j < np; j++)
			printf(" %10.3e", a[i * n + j]);
		printf("\n");
	}
}

void init_matrix(double *a, int m, int n, int k)
{
	double (*q)(int, int, int, int);
	double (*f[])(int, int, int, int) = {f1, f2, f3, f4};
	int i, j;
	q = f[k-1];
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			a[i * n + j] = q(m, n, i+1, j+1);
}
