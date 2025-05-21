#include <stdio.h>
#include <time.h>
#include <math.h>

#include "init_f.h"
#include "solve.h"

/* ./a.out a b eps M k */
int main(int argc, char *argv[])
{
	double t, a, b, eps, x = 0;
	int m, k, cl, it, task = 5;
	
	double (*f) (double);
	double (*f_lst[]) (double) = {f0, f1, f2, f3, f4, f5, f6}; //TODO: Rem f7
	int len_f = sizeof(f_lst) / sizeof(f_lst[0]);

	if (
			!((argc == 6) && 
			sscanf(argv[1], "%lf", &a) == 1 &&
			sscanf(argv[2], "%lf", &b) == 1 &&
			(a <= b) &&
			(sscanf(argv[3], "%lf", &eps) == 1 && (eps >= 0)) &&
			((sscanf(argv[4], "%d", &m) == 1) && m > 0) &&
			((sscanf(argv[5], "%d", &k) == 1) && ((0 <= k) && (k < len_f))))
	) {
		fprintf(stderr, "Usage: %s a b eps M k\n", argv[0]);
		return -1;
	}

	f = f_lst[k];

	t = clock();
	it = t5_solve(f, a, b, eps, m, &x);
	t = (clock() - t) / CLOCKS_PER_SEC;
		
	cl = get_call_count();
	
	if (it < 0)
	{
		fprintf(stdout, "%s : Task = %d NOT FOUND Count = %d T = %.2f\n", argv[0], task, cl, t);
		return -2;
	} else 
	{
		printf("%s : Task = %d X = %e Res = %e Its = %d Count = %d T = %.2f\n", argv[0], task, x, f(x), it, cl, t);
		return 0;
	}
}

