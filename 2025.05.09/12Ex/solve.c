#include "solve.h"

#include <math.h>
#include <float.h>

#define MAX_ITER 30

int t12_solve (
		double (*xt) (double), 
		double (*yt) (double),
		double a, double b,
		double eps, double *res
) {
	int it;

	int n = 1;
	double h = (b - a) * 0.5;
	double x = xt(b) - xt(a);
	double y = yt(b) - yt(a);
	double len_n = sqrt(x * x + y * y);

	for (it = 1; it <= MAX_ITER; ++it)
	{
		double t = a;
		double tn = a + h;
		double len_2n = 0;
	
		for (int i = 0; i < n; i++)
		{
			x = xt(tn) - xt(t);
			y = yt(tn) - yt(t);
			len_2n += sqrt(x * x + y * y);

			t = tn;
			tn += h;
		}

		h *= 0.5;

		if (fabs(len_2n - len_n) < eps)
			break;
		
		len_n = len_2n;
		n <<= 1;
	}

	if (it > MAX_ITER) 
		return -1;
	
	*res = len_n;

	return n;
}

