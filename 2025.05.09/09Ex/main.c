#include <stdio.h>
#include <time.h>
#include <math.h>
#include <float.h>

#include "init_f.h"
#include "solve.h"

/* ./a09.out a b eps k */
int main (int argc, char *argv[])
{
	double t, integral, a, b, eps;
	int k, n, calls, task = 9;
	
	double (*f_lst[]) (double) = {f0, f1, f2, f3, f4, f5, f6};
	int len_f = sizeof(f_lst) / sizeof(f_lst[0]);

	if (
			!((argc == 5) && 
			sscanf(argv[1], "%lf", &a) == 1 &&
			sscanf(argv[2], "%lf", &b) == 1 &&
			((sscanf(argv[3], "%lf", &eps) == 1) && (eps > 0)) &&
			((sscanf(argv[4], "%d", &k) == 1) && ((0 <= k) && (k < len_f))))
	) {
		fprintf(stderr, "Usage: %s a b eps k\n", argv[0]);
		return -1;
	}


	t = clock();
	n = t9_solve(f_lst[k], a, b, eps, &integral);
	t = (clock() - t) / CLOCKS_PER_SEC;
	
	calls = get_call_count();

	if (n < 0) {
		fprintf (stdout, "%s : Task = %d Method is not applicable Count = %d T = %.2f\n", argv[0], task, calls, t);
		return -2;
	} else {
		fprintf (stdout, "%s : Task = %d Res = %e N = %d Count = %d T = %.2f\n", argv[0], task, integral, n, calls, t);
		return 0;
	}
}

