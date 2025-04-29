#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <math.h>

#include "init_f.h"
#include "status.h"
#include "solve.h"

/* ./a.out a b eps M k */
int main(int argc, char *argv[])
{
	double t, a, b, eps, x = 0;
	int m, k, task = 1;
	status ret;
	
	double (*f) (double);
	double (*f_lst[]) (double) = {f0, f1, f2, f3, f4, f5, f6};

	if (
			!((argc == 6) && 
			sscanf(argv[1], "%lf", &a) == 1 &&
			sscanf(argv[2], "%lf", &b) == 1 &&
			sscanf(argv[3], "%lf", &eps) == 1 &&
			((sscanf(argv[4], "%d", &m) == 1) && m > 0) &&
			((sscanf(argv[5], "%d", &k) == 1) && ((0 <= k) && (k <= 6))))
	) {
		fprintf(stderr, "Usage: %s a b eps M k\n", argv[0]);
		return 1;
	}

	f = f_lst[k];

	t = clock();
	ret = t1_solve(f, a, b, eps, m, &x);
	t = (clock() - t) / CLOCKS_PER_SEC;

	do {
		switch (ret) 
		{
			case SUCCESS:
				continue;
			case MORE_ONE_ROOT:
				continue;
			case RUN_TIME:
				break;
		}
		
		fprintf(stdout, "Error: with code %d - The method is not applicable!\n", ret);

		return ret;
	} while (0);

	if (ret == MORE_ONE_ROOT)
		printf("%s : Task = %d NOT FOUND Count = %d T = %.2f\n", argv[0], task, count, t);
	else 
		printf("%s : Task = %d X = %e Res = %e Its = %d Count = %d T = %.2f\n", argv[0], task, x, f(x), it, count, t);

	return 0;
}

