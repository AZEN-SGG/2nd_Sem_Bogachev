#include "solve.h"
#include "comp.h"
#include "polynom.h"

#include <math.h>
#include <float.h>

int t6_solve (
		double (*f) (double), 
		const int m, double *d,
		double a, double b, 
		const double eps, const int M, double *res
) {
	const int len = m + 1;
	
	double *y_lst = d;
	double *x_lst = d + len;
	double *t_lst = d + (len << 1);

	int it;

	if (is_eps(y_lst[0], eps)) {
		*res = a;
		return 1;
	} else if (is_eps(y_lst[m], eps)) {
		*res = b;
		return 1;
	}

	for (it = 1; it <= M; ++it)
	{
		double maximum = 0;
		int max_i = 0;

		double x = construct_poly(0, len, y_lst, x_lst);
		double y = f(x);

		if (is_eps(y, eps))
		{
			*res = x;
			return it;
		}

		// Возвращение значений функции в x_lst можно было встроить в суммирование полинома, но мало толку
		for (int i = 0; i < len; ++i)
		{
			double xi = t_lst[i];
			double yi = y_lst[i];

			x_lst[i] = xi;

			if (is_equal(y, yi))
				return -1;
			
			if ((yi - maximum) > DBL_EPSILON) {
				maximum = yi;
				max_i = i;
			}
		}
		
		y_lst[max_i] = y;
		x_lst[max_i] = x;
		t_lst[max_i] = x;
	}

	return -1;
}

