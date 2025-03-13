#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_io.h"
#include "io_status.h"
#include "solve.h"

/* ./a.out n m p k_a [filename_a] k_b [filename_b] */
int main(int argc, char *argv[])
{
	double t, res, *a, *b;
	int n, m, p, k_a, k_b, task = 6;
	char *name_a = 0, *name_b = 0;
	if (!((argc == 6 || argc == 7 || argc == 8) && 
				sscanf(argv[1], "%d", &n) == 1 && 
				sscanf(argv[2], "%d", &m) == 1 && 
				sscanf(argv[3], "%d", &p) == 1 && 
				sscanf(argv[4], "%d", &k_a) == 1 && 
				(k_a >= 0 && k_a <= 4) &&
				(!(k_a == 0 && argc == 6)) && 
				((k_a == 0 && sscanf(argv[6], "%d", &k_b) == 1) || 
				 (k_a != 0 && sscanf(argv[5], "%d", &k_b) == 1)) &&
				(k_b >= 0 && k_b <= 4) && 
				(!(k_b == 0 && argc == 6)) && 
				(!((k_a == 0 && k_b == 0) && argc != 8))))
	{
		printf("Usage: %s n m p k_a [filename_a] k_b [filename_b]\n", argv[0]);
		return 1;
	}
	if (argc != 6) 
	{
		int i_b = 6;
		if (k_a == 0) {name_a = argv[5];i_b++;}
		if (k_b == 0) name_b = argv[i_b];
	}

	a = (double *)malloc(n * m * sizeof(double));
	if (!a)
	{
		printf("Not enough memory\n");
		return 2;
	}
	b = (double *)malloc(m * n * sizeof(double));
	if (!b)
	{
		free(a);
		printf("Not enough memory\n");
		return 2;
	}

	if (name_a)
	{ /* из файла */
		io_status ret;
		ret = read_matrix(a, n, m, name_a);
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
			free(b);
			return 3;
		} while (0);
	} else init_matrix(a, n, m, k_a);

	if (name_b)
	{
		io_status ret;
		ret = read_matrix(b, m, n, name_b);
		do {
			switch (ret)
			{
				case SUCCESS:
					continue;
				case ERROR_OPEN:
					printf("Cannot open %s\n", name_b);
					break;
				case ERROR_READ:
					printf("Cannot read %s\n", name_b);
					break;
			}
			free(a);
			free(b);
			return 3;
		} while (0);
	} else init_matrix(b, m, n, k_b);

	printf("Matrix A:\n");
	print_matrix(a, n, m, p);
	printf("Matrix B:\n");
	print_matrix(b, m, n, p);

	t = clock();
	res = t6_solve(a, b, n, m);
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf ("%s : Task = %d Result = %e Elapsed = %.2f\n", argv[0], task, res, t);

	free(a);
	free(b);

	return 0;
}
