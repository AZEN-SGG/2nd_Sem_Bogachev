#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <math.h>

#include "array_io.h"
#include "io_status.h"
#include "solve.h"

/* ./a.out x_0 n filename */
int main(int argc, char *argv[])
{
	double x_0, t, r = 0, *X = 0, *Y = 0;
	int n, task = 1;
	char *name = 0;
	io_status ret;

	if (
			!((argc == 4) && 
			sscanf(argv[1], "%le", &x_0) == 1 &&
			((sscanf(argv[2], "%d", &n) == 1) && n > 0) &&
			((name = argv[3]) && name))
	) {
		fprintf(stderr, "Usage: %s x_0 n filename\n", argv[0]);
		return 1;
	}

	X = (double *)malloc(n * sizeof(double));
	if (!X)
	{
		fprintf(stderr, "%s\n", ERR_MEM);
		return 2;
	}
	
	Y = (double *)malloc(n * sizeof(double));
	if (!Y)
	{
		free(X);
		fprintf(stderr, "%s\n", ERR_MEM);
		return 2;
	}

	ret = read_values(X, Y, n, name);
	do {
		switch (ret)
		{
			case SUCCESS:
				continue;
			case ERROR_OPEN:	
				fprintf(stderr, "%s '%s'!\n", ERR_OPEN, name);
				break;
			case ERROR_READ:
				fprintf(stderr, "%s '%s'!\n", ERR_READ, name);
				break;
		}

		free(X);
		free(Y);

		return 3; 
	} while (0);

	t = clock();
	r = t1_solve(x_0, n, X, Y);
	t = (clock() - t) / CLOCKS_PER_SEC;
	
	if (fabs(r - DBL_MAX) < DBL_EPSILON)
	{
		fprintf(stderr, "%s\n", ERR_FUNC);

		free(X);
		free(Y);

		return 4;
	}

	printf("%s : Task = %d Result = %e Elapsed = %.2f\n", argv[0], task, r, t);

	free(X);
	free(Y);

	return 0;
}

