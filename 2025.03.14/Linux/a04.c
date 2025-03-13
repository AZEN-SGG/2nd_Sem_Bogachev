#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_io.h"
#include "io_status.h"
#include "solve.h"

/* ./a.out n m p k_a [filename_a] k_b [filename_b] k_x [filename_x] */
int main(int argc, char *argv[])
{
	double t, res, *a, *b, *x;
	int n, m, p, k_a, k_b, k_x, task = 4;
	char *name_a = 0, *name_b = 0, *name_x = 0;
	
	if (!((argc >= 7 && argc <= 10) && 
			sscanf(argv[1], "%d", &n) == 1 && 
			sscanf(argv[2], "%d", &m) == 1 && 
			sscanf(argv[3], "%d", &p) == 1 && 
			sscanf(argv[4], "%d", &k_a) == 1 && 
			(k_a >= 0 && k_a <= 4) &&
			(!(k_a == 0 && argc == 7)) && 
			((k_a == 0 && sscanf(argv[6], "%d", &k_b) == 1) || 
			 (k_a != 0 && sscanf(argv[5], "%d", &k_b) == 1)) &&
			(k_b >= 0 && k_b <= 4) && 
			(!(k_b == 0 && ((argc <= 7) || (k_a == 0 && argc <= 8)))) &&
			((k_a == 0 && k_b == 0 && sscanf(argv[8], "%d", &k_x) == 1) || 
			 (k_a != 0 && k_b != 0 && sscanf(argv[6], "%d", &k_x) == 1) ||
			 (sscanf(argv[7], "%d", &k_x) == 1)) && 
		       (k_x >= 0 && k_x <= 4) && 
		       (!(k_x == 0 && ((k_a == 0 && k_b == 0 && argc != 10) || 
					(k_a != 0 && k_b != 0 && argc != 8) ||
					(k_a != k_b && argc != 9)))))) 	
	{
		printf("Usage: %s n m p k_a [filename_a] k_b [filename_b] k_x [filename_x]\n", argv[0]);
		return 1;
	}
	
	if (argc != 7) 
	{
		int i_b = 6;
		if (k_a == 0) { name_a = argv[5]; i_b++; }
		if (k_b == 0) { name_b = argv[i_b]; i_b+=2; }
		else i_b++;
		if (k_x == 0) name_x = argv[i_b];
	}

	a = (double *)malloc(n * m * sizeof(double));
	if (!a)
	{
		printf("Not enough memory\n");
		return 2;
	}
	
	b = (double *)malloc(n * sizeof(double));
	if (!b)
	{
		free(a);
		printf("Not enough memory\n");
		return 2;
	}
	
	x = (double *)malloc(m * sizeof(double));
	if (!x)
	{
		free(a);
		free(b);
		printf("Not enough memory\n");
		return 2;
	}

	if (name_a)
	{ /* Читаем матрицу A из файла */
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
			free(x);
			return 3;
		} while (0);
	} 
	else init_matrix(a, n, m, k_a);

	if (name_b)
	{ /* Читаем матрицу B из файла */
		io_status ret;
		ret = read_matrix(b, n, 1, name_b);
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
			free(x);
			return 3;
		} while (0);
	} 
	else init_matrix(b, n, 1, k_b);

	if (name_x)
	{ /* Читаем матрицу X из файла */
		io_status ret;
		ret = read_matrix(x, m, 1, name_x);
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
			free(b);
			free(x);
			return 3;
		} while (0);
	} 
	else init_matrix(x, m, 1, k_x);

	printf("Matrix:\n");
	print_matrix(a, n, m, p);
	printf("Initial vector b:\n");
	print_matrix(b, n, 1, p);
	printf("Initial vector x:\n");
	print_matrix(x, m, 1, p);

	t = clock();
	res = t4_solve(a, x, b, m, n);
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf ("%s : Task = %d Result = %e Elapsed = %.2f\n", argv[0], task, res, t);

	free(a);
	free(b);
	free(x);

	return 0;
}
