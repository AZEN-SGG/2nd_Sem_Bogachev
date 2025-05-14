#include "solve.h"

#include <math.h>
#include <float.h>

#define MAX_ITER 30

int t9_solve (
		double (*f) (double), 
		double a, double b,
		double eps, double *res
) {
	int it;
	double integ_n;

	int n = 2;
	double h = (b - a) * 0.5;
	double s1 = (f(a) + f(b)) * h/3;
	double s2 = f(a + h) * h*4/3;

	for (it = 1; it <= MAX_ITER; ++it)
	{
		double x = a + h*0.5;
		double s2_2n = 0;

		for (int i = 0; i < n; i++)
		{
			s2_2n += f(x);
			x += h;
		}

		s2_2n *= h*2/3;

		if (fabs((s2_2n - s1 * 0.5) - s2 * 0.75) < eps) {
			integ_n = s1 + s2;
			break;
		}
		
		s1 = s1 * 0.5 + s2 * 0.25;
		s2 = s2_2n;

		h *= 0.5;
		n <<= 1;
	}

	if (it > MAX_ITER) 
		return -1;
	
	*res = integ_n;

	return n;
}

