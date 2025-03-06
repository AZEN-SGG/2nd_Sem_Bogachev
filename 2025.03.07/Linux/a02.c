#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_io.h"
#include "io_status.h"
#include "solve.h"

/* ./a.out n p k [filename] */
int main(int argc, char *argv[])
{
	double t, res, *a;
	int n, p, k, task = 2;
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
	if (argc == 5) name = argv[4];

	a = (double *)malloc(n * n * sizeof(double));
	if (!a)
	{
		printf("Not enough memory\n");
		return 2;
	}

	if (name)
	{ /* из файла */
		io_status ret;
		ret = read_sq_matrix(a, n, name);
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
			return 3;
		} while (0);
	} else init_sq_matrix(a, n, k);

	printf("Initial matrix:\n");
	print_sq_matrix(a, n, p);

	t =  clock();
	res = t2_solve(a, n);
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf("Result = %10.3e\n", res);
	printf("%s : Task = %d Elapsed = %.2f\n", argv[0], task, t);
	free(a);
	return 0;
}
