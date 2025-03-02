#include <stdio.h>
#include "array_io.h"

#define MAX(n, m) (n < m ? n : m)

io_status read_matrix(double *a, int n, int m, const char *name)
{
	int i, j;
	FILE *fp;
	if (!(fp = fopen(name, "r"))) return ERROR_OPEN;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			if (fscanf(fp, "%lf", a + i * m + j) != 1) 
				{fclose(fp); return ERROR_READ;}
	fclose(fp);
	return SUCCESS;
}

void print_matrix(const double *a, int n, int m, int p)
{
	int np = (n > p ? p : n);
	int mp = (m > p ? p : m);
	int i, j;

	for (i = 0; i < np; i++)
	{
		for (j = 0; i < mp; j++)
			printf(" %10.3e", a[i * m + j]);
		printf("\n");
	}
}

void init_matrix(double *a, int n, int m)
{
	double (*f)[](int, int, int, int) = {f1, f2, f3, f4};
	int i, j;
	q = f[k-1];
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			a[i * m + j] = (*q(n, m , i, j));
}
