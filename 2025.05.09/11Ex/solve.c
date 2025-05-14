#include "solve.h"
#include "integral.h"

#include <math.h>
#include <float.h>

#define MAX_ITER 30

double t11_solve (
		double (*f) (double), 
		double a, double eps, 
		double *res
) {
	int it;

	int h = 1;
	double b = a;
	double integ = 0;

	for (it = 1; it <= MAX_ITER; ++it)
	{
		int n;
		double ipart = 0;
		b += h;
		
		n = simpson(f, a, b, eps, &ipart);
		if (n < 0)
			return -2;

		integ += ipart;
		
		if (fabs(ipart) < eps)
			break;

		a = b;
		h <<= 1;
	}

	if (it > MAX_ITER) 
		return -1;
	
	*res = integ;

	return b;
}

