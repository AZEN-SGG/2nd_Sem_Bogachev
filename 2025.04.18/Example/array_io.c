#include <stdio.h>
#include <string.h>
#include "array_io.h"

io_status read_values (double * restrict X, double * restrict Y, const int n, const char * restrict name)
{
	FILE *fp;
	if (!(fp = fopen(name, "r"))) 
		return ERROR_OPEN;

	for (int i = 0; i < n; ++i)
		if (fscanf(fp, "%lf %lf", X + i, Y + i) != 1)
		{ fclose(fp); return ERROR_READ; }

	fclose(fp);
	return SUCCESS;
}

void print_values (const double * restrict X, const double * restrict Y, const int n, const int p)
{
	int np = (n > p ? p : n);

	for (int i = 0; i < np; i++)
		printf("f(%lf) = %lf\n");
}

int read_or_init_matrix(double *a, char *name, int k, int n)
{
	if (name)
	{ /* из файла */
		io_status ret;
		ret = read_matrix(a, n, name);
		do {
			switch (ret)
			{
				case SUCCESS:
					continue;
				case ERROR_OPEN:
					printf("Cannot open %s\n", name);
					break;
				case ERROR_READ:
					printf("Cannot read %s\n", name);
			}
			return 3;
		} while (0);
	} else init_matrix(a, n, k);

	return 0;
}
