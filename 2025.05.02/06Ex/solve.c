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
	double *maximum = d;

	const int len = m + 1;
	
	double *y_lst = d;
	double *x_lst = d + len;
	double *t_lst = d + (len << 1);

	int it;
	for (it = 1; it <= M; ++it)
	{
		double x = construct_poly(0, len, y_lst, x_lst);
		double y = f(x);

		if (is_eps(y, eps))
		{
			*res = x;
			return it;
		}

		// Можно возвращение значений функции в y_lst можно было встроить в суммирование полинома, но мало толку
		for (int i = 0; i < len; ++i)
		{
			double yi = t_lst[i];
			y_lst[i] = yi;

			if (is_equal(y, yi))
				return -1;
			
			if ((fabs(yi) - fabs(*maximum)) > DBL_EPSILON)
				maximum = &yi;
		}

		*maximum = y;
		*(maximum + len) = x;
		*(maximum + (len << 1)) = y;
	}

	(void)a;
	(void)b;

	return -1;
}

