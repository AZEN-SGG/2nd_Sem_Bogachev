#include <stdio.h>
#include <string.h>
#include "array_io.h"

io_status read_values (double * restrict X, double * restrict Y, const int n, const char * restrict name)
{
	FILE *fp;
	if (!(fp = fopen(name, "r"))) 
		return ERROR_OPEN;

	for (int i = 0; i < n; ++i)
		if (fscanf(fp, "%lf\t%lf", X + i, Y + i) != 2)
		{ fclose(fp); return ERROR_READ; }

	fclose(fp);
	return SUCCESS;
}

io_status read_values_and_derivatives (
		double * restrict X, 
		double * restrict Y, 
		double * restrict D, 
		const int n, 
		const char * restrict name
		)
{
	FILE *fp;
	if (!(fp = fopen(name, "r"))) 
		return ERROR_OPEN;

	for (int i = 0; i < n; ++i)
		if (fscanf(fp, "%lf\t%lf\t%lf", X + i, Y + i, D + i) != 3)
		{ fclose(fp); return ERROR_READ; }

	fclose(fp);
	return SUCCESS;
}

void print_values (const double * restrict X, const double * restrict Y, const int n, const int p)
{
	int np = (n > p ? p : n);

	for (int i = 0; i < np; i++)
		printf("f(%lf) = %lf\n", X[i], Y[i]);
}

void print_values_and_derivatives (
		const double * restrict X, 
		const double * restrict Y, 
		const double * restrict D, 
		const int n, const int p
		) 
{
	int np = (n > p ? p : n);

	for (int i = 0; i < np; i++)
		printf("f(%lf) = %lf, f`(%lf) = %lf\n", X[i], Y[i], X[i], D[i]);
}

