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
	
	double xa = xt(a), ya = yt(a);
	double xb = xt(b), yb = yt(b);
	double xl = xa, yl = yb;

	int n = 2;
	double h = (b - a) * 0.5;
	double x = xb - xl;
	double y = yb - yl;
	double len_n = sqrt(x * x + y * y);

	for (it = 1; it <= MAX_ITER; ++it)
	{
		double tn = a + h;
		double len_2n = 0;

		for (int i = 1; i < n; i++)
		{
			double xc = xt(tn);
			double yc = yt(tn);

			x = xc - xl;
			y = yc - yl;
			len_2n += sqrt(x * x + y * y);
			
			xl = xc;
			yl = yc;
			tn += h;
		}

		x = xb - xl;
		y = yb - yl;
		len_2n += sqrt(x * x + y * y);

		h *= 0.5;

		if (fabs(len_2n - len_n) < eps)
			break;
		
		xl = xa;
		yl = ya;

		len_n = len_2n;
		n <<= 1;
	}

	if (it > MAX_ITER) 
		return -1;
	
	*res = len_n;

	return n;
}

