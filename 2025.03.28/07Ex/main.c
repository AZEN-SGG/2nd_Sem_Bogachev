#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "array_io.h"
#include "io_status.h"
#include "matrix.h"
#include "solve.h"

/* ./a.out t m n p k_a [filename_a] k_x [filename_x] */
int main(int argc, char *argv[])
{
	double tau, t, r1, r2, *a, *x_0, *b, *x, *r;
	int n, m, p, k_a, k_x, task = 7;
	char *name_a = 0, *name_x = 0;
	if (!((argc == 7 || argc == 8 || argc == 9) && 
				sscanf(argv[1], "%lf", &tau) == 1 && 
				sscanf(argv[2], "%d", &m) == 1 && 
				sscanf(argv[3], "%d", &n) == 1 && 
				sscanf(argv[4], "%d", &p) == 1 && 
				sscanf(argv[5], "%d", &k_a) == 1 && 
				(k_a >= 0 && k_a <= 4) &&
				(!(k_a == 0 && argc == 7)) && 
				((k_a == 0 && sscanf(argv[7], "%d", &k_x) == 1) || 
				 (k_a != 0 && sscanf(argv[6], "%d", &k_x) == 1)) &&
				(k_x >= 0 && k_x <= 4) && 
				(!(k_x == 0 && argc == 7)) && 
				(!((k_a == 0 && k_x == 0) && argc != 9))))
	{
		printf("Usage: %s t m n p k_a [filename_a] k_x [filename_x]\n", argv[0]);
		return 1;
	}
	if (argc != 7) 
	{
		int i_x = 7;
		if (k_a == 0) { name_a = argv[6]; i_x++; }
		if (k_x == 0) name_x = argv[i_x];
	}

	a = (double *)malloc((size_t)n * (size_t)n * sizeof(double));
	if (!a)
	{
		printf("Not enough memory\n");
		return 2;
	}
	x_0 = (double *)malloc((size_t)n * sizeof(double));
	if (!x_0)
	{
		free(a);
		printf("Not enough memory\n");
		return 2;
	}
	b = (double *)malloc((size_t)n * sizeof(double));
	if (!b)
	{
		free(a);
		free(x_0);
		printf("Not enough memory\n");
		return 2;
	}
	x = (double *)malloc((size_t)n * sizeof(double));
	if (!x)
	{
		free(a);
		free(x_0);
		free(b);
		printf("Not enough memory\n");
		return 2;
	}
	r = (double *)malloc((size_t)n * sizeof(double));
	if (!r)
	{
		free(a);
		free(x_0);
		free(b);
		free(x);
		printf("Not enough memory\n");
		return 2;
	}

	if (name_a)
	{ /* из файла */
		io_status ret;
		ret = read_matrix(a, n, n, name_a);
		do {
			switch (ret)
			{
				case SUCCESS:
					continue;
				case ERROR_OPEN:
					printf("Cannot open %s\n", name_a);
					break;
				case ERROR_READ:
					printf("Cannot read %s\n", name_a);
					break;
			}
			free(a);
			free(x_0);
			free(b);
			free(x);
			free(r);
			return 3;
		} while (0);
	} else init_matrix(a, n, n, k_a);

	if (name_x)
	{
		io_status ret;
		ret = read_matrix(x_0, n, 1, name_x);
		do {
			switch (ret)
			{
				case SUCCESS:
					continue;
				case ERROR_OPEN:
					printf("Cannot open %s\n", name_x);
					break;
				case ERROR_READ:
					printf("Cannot read %s\n", name_x);
					break;
			}
			free(a);
			free(x_0);
			free(b);
			free(x);
			free(r);
			return 3;
		} while (0);
	} else init_matrix(x_0, n, 1, k_x);

	init_vec_b(a, b, n);

	printf("Matrix A:\n");
	print_matrix(a, n, n, p);
	printf("Vector x_0:\n");
	print_matrix(x_0, 1, n, p);
	printf("Vector b:\n");
	print_matrix(b, 1, n, p);

	t = omp_get_wtime();
	t7_solve(a, x_0, b, x, r, n, m, tau);
	t = omp_get_wtime() - t;
	
	r1 = get_r1(a, x, b, n);
	r2 = get_r2_value(x, n);

	printf("New vector:\n");
	print_matrix(x, 1, n, p);
	printf("%s : Task = %d Res1 = %e Res2 = %e Elapsed = %.2f\n", argv[0], task, r1, r2, t);

	free(a);
	free(x_0);
	free(b);
	free(x);
	free(r);

	return 0;
}
