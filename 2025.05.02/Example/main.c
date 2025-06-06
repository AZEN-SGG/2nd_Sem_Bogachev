#include <stdio.h>
#include <time.h>
#include <math.h>

#include "init_f.h"
#include "status.h"
#include "solve.h"

/* ./a.out a b eps M k */
int main(int argc, char *argv[])
{
	double t, a, b, eps, x = 0;
	int m, k, cl, it = 0, task = 1;
	status ret;
	
	double (*f) (double);
	double (*f_lst[]) (double) = {f0, f1, f2, f3, f4, f5, f6, sin};
	int len_f = sizeof(f_lst) / sizeof(f_lst[0]);

	if (
			!((argc == 6) && 
			sscanf(argv[1], "%lf", &a) == 1 &&
			sscanf(argv[2], "%lf", &b) == 1 &&
			sscanf(argv[3], "%lf", &eps) == 1 &&
			((sscanf(argv[4], "%d", &m) == 1) && m > 0) &&
			((sscanf(argv[5], "%d", &k) == 1) && ((0 <= k) && (k <= len_f))))
	) {
		fprintf(stderr, "Usage: %s a b eps M k\n", argv[0]);
		return 1;
	}

	f = f_lst[k];

	t = clock();
	ret = t1_solve(f, a, b, eps, m, &x, &it);
	t = (clock() - t) / CLOCKS_PER_SEC;
	
	cl = get_call_count();

	do {
		switch (ret) 
		{
			case SUCCESS:
				continue;
			case RUN_TIME:
				fprintf(stderr, "Error: with code %d - Not enough iterations!\n", ret);
				break;
			case MORE_ONE_ROOT:
				fprintf(stderr, "Error: with code %d - The same signs on the boundaries of the segment!\n", ret);
				break;
			case HIGH_ERROR:
				fprintf(stderr, "Error: with code %d - The solution was found with a high error rate!\n", ret);
				break;
		}
		
		fprintf(stdout, "%s : Task = %d NOT FOUND Count = %d T = %.2f\n", argv[0], task, cl, t);
		return ret;
	} while (0);

	printf("%s : Task = %d X = %e Res = %e Its = %d Count = %d T = %.2f\n", argv[0], task, x, f(x), it, cl, t);

	return 0;
}

