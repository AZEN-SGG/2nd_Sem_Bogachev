#include <stdio.h>
#include <time.h>
#include <math.h>

#include "init_f.h"
#include "solve.h"

/* ./a.out x_0 eps M k */
int main(int argc, char *argv[])
{
	double t, x_0, eps, x = 0;
	int m, k, cl, it, task = 2;
	
	double (*f) (double);
	double (*f_lst[]) (double) = {f0, f1, f2, f3, f4, f5, f6, sin}; // TODO: Remove sin
	double (*d_lst[]) (double) = {d0, d1, d2, d3, d4, d5, d6, cos}; // TODO: Remove cos
	int len_f = sizeof(f_lst) / sizeof(f_lst[0]);


	if (
			!((argc == 5) && 
			sscanf(argv[1], "%lf", &x_0) == 1 &&
			(sscanf(argv[2], "%lf", &eps) == 1 && (eps >= 0)) &&
			((sscanf(argv[3], "%d", &m) == 1) && (m > 0)) &&
			((sscanf(argv[4], "%d", &k) == 1) && ((0 <= k) && (k <= len_f))))
	) {
		fprintf(stderr, "Usage: %s x_0 eps M k\n", argv[0]);
		return -1;
	}

	f = f_lst[k];

	t = clock();
	it = t2_solve(f, d_lst[k], x_0, eps, m, &x);
	t = (clock() - t) / CLOCKS_PER_SEC;
		
	cl = get_call_function_count();

	if (it >= m)
	{
		fprintf(stdout, "%s : Task = %d NOT FOUND Count = %d T = %.2f\n", argv[0], task, cl, t);
		return -2;
	} else
	{
		printf("%s : Task = %d X = %e Res = %e Its = %d Count = %d T = %.2f\n", argv[0], task, x, f(x), it, cl, t);
		return 0;
	}
}

