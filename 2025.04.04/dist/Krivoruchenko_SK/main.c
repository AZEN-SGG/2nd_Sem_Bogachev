#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "array_io.h"
#include "io_status.h"
#include "matrix.h"
#include "solve.h"

/* ./a.out n p k [filename] */
int main(int argc, char *argv[])
{
	double t, *a, *x, r1 = 0, r2 = 0;
	int n, p, k, res = 0, *c, task = 14;
	char *name = 0;
	
	if (!((argc == 4 || argc == 5) && 
				sscanf(argv[1], "%d", &n) == 1 && 
				sscanf(argv[2], "%d", &p) == 1 &&
				sscanf(argv[3], "%d", &k) == 1 &&
				k >= 0 && k <= 4 && (!(k == 0 && argc != 5))))
	{
		printf("Usage: %s n p k [filename]\n", argv[0]);
		return 1;
	}
	if (argc == 5 && k == 0) name = argv[4];

	a = (double *)malloc(n * n * sizeof(double));
	if (!a)
	{
		printf("Not enough memory\n");
		return 2;
	}
	
	x = (double *)malloc(n * n * sizeof(double));
	if (!x)
	{
		free(a);
		printf("Not enough memory\n");
		return 2;
	}
	c = (int *)malloc(n * sizeof(int));
	if (!c)
	{
		free(a);
		free(x);
		printf("Not enough memory\n");
		return 2;
	}

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
			free(a);
			free(x);
			free(c);
			return 3;
		} while (0);
	} else init_matrix(a, n, k);

	init_identity_matrix(x, n);

	#pragma omp simd
	for (int i = 0; i < n; ++i)
		c[i] = i;

	printf("Initial matrix:\n");
	print_matrix(a, n, p);

	t = omp_get_wtime();
	res = t14_solve(n, a, x, c);
	t = omp_get_wtime() - t;
	
	if (res == SINGULAR) 
	{
		free(a);
		free(x);
		free(c);

		printf("The matrix is degenerate\n");
		return 4;	
	}	

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
			free(a);
			free(x);
			free(c);
			return 3;
		} while (0);
	} else init_matrix(a, n, k);
	
	r1 = get_r1(n, a, x);	
	r2 = get_r2(n, a, x);	
	
	printf("Inverse matrix:\n");
	print_matrix(x, n, p);
	printf("%s : Task = %d Res1 = %e Res2 = %e Elapsed = %.2f K = %d N = %d\n", argv[0], task, r1, r2, t, k, n);

	free(a);
	free(x);
	free(c);

	return 0;
}
