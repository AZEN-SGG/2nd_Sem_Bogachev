#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

	res = read_or_init_matrix(a, name, k, n);
	if (res)
	{
		free(a);
		free(x);
		free(c);

		return res;
	}

	init_identity_matrix(x, n);

	for (int i = 0; i < n; ++i)
		c[i] = i;

	printf("Initial matrix:\n");
	print_matrix(a, n, p);

	t = clock();
	res = t14_solve(n, a, x, c);
	t = (clock() - t) / CLOCKS_PER_SEC;
	
	if (res == SINGULAR) 
	{
		free(a);
		free(x);
		free(c);

		printf("The matrix is degenerate\n");
		return 4;	
	}	

	res = read_or_init_matrix(a, name, k, n);
	if (res)
	{
		free(a);
		free(x);
		free(c);

		return res;
	}
	
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
