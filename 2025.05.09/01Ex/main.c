#include <stdio.h>
#include <time.h>
#include <math.h>
#include <float.h>

#include "init_f.h"
#include "solve.h"

/* ./a01.out x h k */
int main (int argc, char *argv[])
{
	double t, x, h, d;
	int k, cl, task = 1;
	
	double (*f_lst[]) (double) = {f0, f1, f2, f3, f4, f5, f6};
	int len_f = sizeof(f_lst) / sizeof(f_lst[0]);

	if (
			!((argc == 4) && 
			sscanf(argv[1], "%lf", &x) == 1 &&
			((sscanf(argv[2], "%lf", &h) == 1) && (h > 0)) &&
			((sscanf(argv[3], "%d", &k) == 1) && ((0 <= k) && (k < len_f))))
	) {
		fprintf(stderr, "Usage: %s x h k\n", argv[0]);
		return -1;
	}


	t = clock();
	d = t1_solve(f_lst[k], x, h);
	t = (clock() - t) / CLOCKS_PER_SEC;
	
	cl = get_call_count();

	if (fabs(d - DBL_MAX) < DBL_EPSILON)
	{
		fprintf (stdout, "%s : Task = %d Method is not applicable Count = %d T = %.2f\n", argv[0], task, cl, t);
		return -2;
	} else
	{
		fprintf (stdout, "%s : Task = %d Res = %e Count = %d T = %.2f\n", argv[0], task, d, cl, t);
		return 0;
	}
}

