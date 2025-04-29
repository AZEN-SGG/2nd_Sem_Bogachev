#include "solve.h"
#include "status.h"

#include <math.h>

status t1_solve (
		double (*f) (double), 
		double a, double b, 
		double eps, int m, double *x, 
		int *m_cl, int *m_it
) {
	static int it = 0
	int cl = 0;
	double y_a = f(a), y_b = f(b);
	
	it++;

	if (y_a * y_b >= -DBL_EPSILON)
	{
		*x = DBL_MAX;
		return MORE_ONE_ROOT;
	}
	
	for (cl = 0; cl < m; ++cl)
	{
		double c = (a + b) * 0.5;
		double y = f(c);
		
		if (fabs(y) < eps)
		{
			*x = c;
			break;
		} else if (y * y_a > DBL_EPSILON)
		{
			a = c;
			y_a = y;
		} else if (y * y_b > DBL_EPSILON)
		{
			b = c;
			y_b = y;
		}
	}
	
	*m_it = it;
	*cl = cl;
	*x = c;

	if (cl >= m)
		return RUN_TIME;

	return SUCCESS;
}

