#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_io.h"
#include "io_status.h"
#include "solve.h"

/* ./a.out m n p k_a [filename_a] k_x [filename_x] */
int main(int argc, char *argv[])
{
	double t, *a, *x;
	int n, m, p, k_a, k_x, r1, r2, task = 1;
	char *name_a = 0, *name_x = 0;
	if (!((argc == 6 || argc == 7 || argc == 8) && 
				sscanf(argv[1], "%d", &m) == 1 && 
				sscanf(argv[2], "%d", &n) == 1 && 
				sscanf(argv[3], "%d", &p) == 1 && 
				sscanf(argv[4], "%d", &k_a) == 1 && 
				(k_a >= 0 && k_a <= 4) &&
				(!(k_a == 0 && argc == 6)) && 
				((k_a == 0 && sscanf(argv[6], "%d", &k_x) == 1) || 
				 (k_a != 0 && sscanf(argv[5], "%d", &k_x) == 1)) &&
				(k_x >= 0 && k_x <= 4) && 
				(!(k_x == 0 && argc == 6)) && 
				(!((k_a == 0 && k_x == 0) && argc != 8))))
	{
		printf("Usage: %s m n p k_a [filename_a] k_x [filename_x]\n", argv[0]);
		return 1;
	}
	if (argc != 6) 
	{
		int i_x = 6;
		if (k_a == 0) {name_a = argv[5];i_x++;}
		if (k_x == 0) name_x = argv[i_x];
	}

	a = (double *)malloc(n * n * sizeof(double));
	if (!a)
	{
		printf("Not enough memory\n");
		return 2;
	}
	x = (double *)malloc(n * sizeof(double));
	if (!x)
	{
		free(a);
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
			free(x);
			return 3;
		} while (0);
	} else init_matrix(a, n, n, k_a);

	if (name_x)
	{
		io_status ret;
		ret = read_matrix(x, n, 1, name_x);
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
			free(x);
			return 3;
		} while (0);
	} else init_matrix(x, n, 1, k_x);

	printf("Matrix A:\n");
	print_matrix(a, n, n, p);
	printf("Vector x:\n");
	print_matrix(x, n, 1, p);

	t = clock();
	res = t1_solve(a, x, n, m);
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf("Vector x_m:\n");
	print_matrix(x, 1, n, p);
	printf("%s : Task = %d Res1 = %e Res2 = %e Elapsed = %.2f\n", argv[0], task, r1, r2, t);

	free(a);
	free(x);

	return 0;
}
