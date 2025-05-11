#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "init_f.h"
#include "array_io.h"
#include "solve.h"

/* ./a.out m a b eps M k */
int main(int argc, char *argv[])
{
	double t = 0, *d, a, b, eps, x = 0;
	int deg_poly, num_iter, k, cl, it, task = 6;
	
	double (*f) (double);
	double (*f_lst[]) (double) = {f0, f1, f2, f3, f4, f5, f6};
	int len_f = sizeof(f_lst) / sizeof(f_lst[0]);

	if (
			!((argc == 7) && 
			sscanf(argv[1], "%d", &deg_poly) == 1 &&
			sscanf(argv[2], "%lf", &a) == 1 &&
			sscanf(argv[3], "%lf", &b) == 1 &&
			(a <= b) &&
			(sscanf(argv[4], "%lf", &eps) == 1 && (eps >= 0)) &&
			((sscanf(argv[5], "%d", &num_iter) == 1) && num_iter > 0) &&
			((sscanf(argv[6], "%d", &k) == 1) && ((0 <= k) && (k < len_f))))
	) {
		fprintf(stderr, "Usage: %s m a b eps M k\n", argv[0]);
		return -1;
	}

	d = (double *)malloc(3 * (deg_poly + 1) * sizeof(double));
	if (!d)
	{
		fprintf(stderr, "Error: Not enough memory!\n");
		return -2;
	}
	
	f = f_lst[k];
	
	it = init_array(f, d, deg_poly, a, b, eps, &x);
	
	if (!it)
	{
		t = clock();
		it = t6_solve(f, deg_poly, d, a, b, eps, num_iter, &x);
		t = (clock() - t) / CLOCKS_PER_SEC;
	}

	cl = get_call_count();
	
	free(d);

	if (it < 0)
	{
		fprintf(stdout, "%s : Task = %d NOT FOUND Count = %d T = %.2f\n", argv[0], task, cl, t);
		return -2;
	} else 
	{
		fprintf(stdout, "%s : Task = %d X = %e Res = %e Its = %d Count = %d T = %.2f\n", argv[0], task, x, f(x), it, cl, t);
		return 0;
	}
}

