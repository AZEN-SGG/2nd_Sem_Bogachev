#include "integral.h"

#include <math.h>
#include <float.h>

#define MAX_ITER 30

int trapezoid (
		double (*f) (double), 
		double a, double b,
		double eps, double *res
) {
	int it;

	double n = 1;
	double h = (b - a);
	double integ_n = (f(a) + f(b)) * h*0.5;

	for (it = 1; it <= MAX_ITER; ++it)
	{
		double x = a + h*0.5;
		double integ_2n = 0;
	
		for (int i = 0; i < n; i++)
		{
			integ_2n += f(x);
			x += h;
		}

		h *= 0.5;
		integ_2n = integ_2n * h + integ_n * 0.5;

		if (fabs(integ_2n - integ_n) < eps)
			break;
		
		integ_n = integ_2n;
		n *= 2;
	}

	if (it > MAX_ITER) 
		return -1;
	
	*res = integ_n;

	return n;
}

