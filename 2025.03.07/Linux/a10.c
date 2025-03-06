#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_io.h"
#include "io_status.h"
#include "solve.h"

/* ./a.out n m k p k_a [filename_a] k_b [filename_b] */
int main(int argc, char *argv[])
{
	double t, *a, *b, *c;
	int n, m, k, p, k_a, k_b, task = 10;
	char *name_a = 0, *name_b = 0;
	
	if (!((argc == 7 || argc == 8 || argc == 9) && 
			sscanf(argv[1], "%d", &n) == 1 && 
			sscanf(argv[2], "%d", &m) == 1 && 
			sscanf(argv[3], "%d", &k) == 1 && 
			sscanf(argv[4], "%d", &p) == 1 && 
			sscanf(argv[5], "%d", &k_a) == 1 && 
			(k_a >= 0 && k_a <= 4) &&
			(!(k_a == 0 && argc == 7)) && 
			((k_a == 0 && sscanf(argv[7], "%d", &k_b) == 1) || 
			 (k_a != 0 && sscanf(argv[6], "%d", &k_b) == 1)) &&
			(k_b >= 0 && k_b <= 4) && 
			(!(k_b == 0 && argc == 7)) && 
			(!((k_a == 0 && k_b == 0) && argc != 9))))
	{
		printf("Usage: %s n m k p k_a [filename_a] k_b [filename_b]\n", argv[0]);
		return 1;
	}
	
	if (argc != 7) 
	{
		int i_b = 7;
		if (k_a == 0) { name_a = argv[6]; i_b++; }
		if (k_b == 0) name_b = argv[i_b];
	}

	a = (double *)malloc(n * m * sizeof(double));
	if (!a)
	{
		printf("Not enough memory\n");
		return 2;
	}
	
	b = (double *)malloc(m * k * sizeof(double));
	if (!b)
	{
		free(a);
		printf("Not enough memory\n");
		return 2;
	}
	
	c = (double *)malloc(n * k * sizeof(double));
	if (!c)
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
			free(c);
			return 3;
		} while (0);
	} 
	else init_matrix(a, n, m, k_a);

	if (name_b)
	{ /* Читаем матрицу B из файла */
		io_status ret;
		ret = read_matrix(b, m, k, name_b);
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
			free(c);
			return 3;
		} while (0);
	} 
	else init_matrix(b, m, k, k_b);

	printf("Initial matrix A:\n");
	print_matrix(a, n, m, p);
	printf("Initial vector b:\n");
	print_matrix(b, m, k, p);

	t = clock();
	matrix_multiply(a, b, c, n, m, k);
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf("Result vector c:\n");
	print_matrix(c, n, k, p);
	printf("%s : Task = %d Elapsed = %.2f\n", argv[0], task, t);

	free(a);
	free(b);
	free(c);

	return 0;
}
