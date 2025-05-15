#include <stdio.h>
#include <time.h>
#include <math.h>
#include <float.h>

#include "init_f.h"
#include "solve.h"

/* ./a12.out a b eps k_x k_y */
int main (int argc, char *argv[])
{
	double t, integral, a, b, eps;
	int x, y, n, calls, task = 12;
	
	double (*f_lst[]) (double) = {f0, f1, f2, f3, f4, f5, f6};
	int len_f = sizeof(f_lst) / sizeof(f_lst[0]);

	if (
			!((argc == 6) && 
			sscanf(argv[1], "%lf", &a) == 1 &&
			sscanf(argv[2], "%lf", &b) == 1 &&
			((sscanf(argv[3], "%lf", &eps) == 1) && (eps > 0)) &&
			((sscanf(argv[4], "%d", &x) == 1) && ((0 <= x) && (x < len_f))) &&
			((sscanf(argv[5], "%d", &y) == 1) && ((0 <= y) && (y < len_f))))
	) {
		fprintf(stderr, "Usage: %s a b eps k_x k_y\n", argv[0]);
		return -1;
	}


	t = clock();
	n = t12_solve(f_lst[x], f_lst[y], a, b, eps, &integral);
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

