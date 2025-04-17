#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "io_status.h"
#include "solve.h"

/* ./a.out x eps */
int main(int argc, char *argv[])
{
	double x, eps, t, r1 = 0, r2 = 0;
	int task = 5;

	if (
			!((argc == 3) && 
			sscanf(argv[1], "%lf", &x) == 1 &&
			((sscanf(argv[2], "%lf", &eps) == 1) && eps > 0))
	) {
		fprintf(stderr, "Usage: %s x eps\n", argv[0]);
		return 1;
	}

	t = clock();
	r1 = fsin(x, eps);
	t = (clock() - t) / CLOCKS_PER_SEC;

	r2 = fabs(r1 - sin(x));

	printf("%s : Task = %d Result = %e Residual = %e Elapsed = %.2f\n", argv[0], task, r1, r2, t);

	return 0;
}

