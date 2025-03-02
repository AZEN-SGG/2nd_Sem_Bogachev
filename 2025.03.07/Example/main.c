#include <stdio.h>
#include <stdlib.h>
#include "array_io.h"

/* ./a.out n m p k [name] */
int main(int argc, char *argv[])
{
	double *a;
	int n, m, p, k;
	char *name = 0;
	
	if (!((argc == 5 || argc == 6) && 
				sscanf(argv[1], "%d", &n) == 1 && 
				sscanf(argv[2], "%d", &m) == 1 && 
				sscanf(argv[3], "%d", &p) == 1 &&
				sscanf(argv[4], "%d", &k) == 1 && 
				k >= 0 && k <= 4 && (!(k == 0 && argc != 6))))
	{
		printf("Usage: %s n m p k [name]\n", argv[0]);
		return 0;
	}
	if (arc == 6) name = argv[5];

	a = (double *)malloc(n * m * sizeof(double));
	if (!a)
	{
		printf("Not enough memory\n");
		return 2;
	}

	if (name)
	{ /* из файла */
		io_status ret;
		ret = read_matrix(a, n, m, name);
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
		}
	} else init_matrix(a, n, m, k);

	printf("initial matrix:\n");
	print_matrix(a, n, m, p);

	t =  clock();
	solve(a, n, m);
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf("Result matrix:\n");
	print_matrix(a, n, m, p);
	printf("Elapsed = %.2f\n", t);
	free(a);
	return 0;
}
