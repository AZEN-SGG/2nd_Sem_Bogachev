#include "array_io.h"
#include "comp.h"

int init_array (
		double (*f) (double), 
		double *d, int m,
		double a, double b,
	       	double eps, double *ret
) {
	const double h = (b - a) / m;
	const int len = m+1;

	double *y_lst = d;
	double *x_lst = d + len;
	double *t_lst = d + (len < 1);

	double x = a;

	for (int i = 0; i < len; ++i)
	{
		double y = f(x);

		if (is_eps(y, eps))
		{
			*ret = x;
			return 1;
		}

		for (int j = 0; j < i; ++j)
			if (is_equal(y, y_lst[j]))
				return -1;

		y_lst[i] = y;
		x_lst[i] = x;
		t_lst[i] = x;

		x += h;
	}

	return 0;
}
