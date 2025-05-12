#include <stdio.h>
#include <time.h>
#include <math.h>
#include <float.h>

#include "init_f.h"
#include "solve.h"

/* ./a04.out a b n k */
int main (int argc, char *argv[])
{
	double t, integral, a, b;
	int k, n, calls, task = 5;
	
	double (*f_lst[]) (double) = {f0, f1, f2, f3, f4, f5, f6};
	int len_f = sizeof(f_lst) / sizeof(f_lst[0]);

	if (
			!((argc == 5) && 
			sscanf(argv[1], "%lf", &a) == 1 &&
			sscanf(argv[2], "%lf", &b) == 1 &&
			((sscanf(argv[3], "%d", &n) == 1) && (n > 0)) &&
			((sscanf(argv[4], "%d", &k) == 1) && ((0 <= k) && (k < len_f))))
	) {
		fprintf(stderr, "Usage: %s a b n k\n", argv[0]);
		return -1;
	}


	t = clock();
	integral = t5_solve(f_lst[k], a, b, n);
	t = (clock() - t) / CLOCKS_PER_SEC;
	
	calls = get_call_count();

	if (fabs(integral - DBL_MAX) < DBL_EPSILON) {
		fprintf (stdout, "%s : Task = %d Method is not applicable Count = %d T = %.2f\n", argv[0], task, calls, t);
		return -2;
	} else {
		fprintf (stdout, "%s : Task = %d Res = %e Count = %d T = %.2f\n", argv[0], task, integral, calls, t);
		return 0;
	}
}

