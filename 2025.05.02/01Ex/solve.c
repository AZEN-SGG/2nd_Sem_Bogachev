#include "solve.h"
#include "status.h"

#include <math.h>
#include <float.h>

status t1_solve (
		double (*f) (double), 
		double a, double b, 
		double eps, int m, double *x, int *m_it
) {
	int it = 0;
	status ret = SUCCESS;
	double c = DBL_MAX, y, y_a = f(a), y_b = f(b);


	if (y_a * y_b >= -DBL_EPSILON)
	{
		*x = DBL_MAX;
		return MORE_ONE_ROOT;
	}
	
	for (it = 0; it < m; ++it)
	{
		c = (a + b) * 0.5;
		y = f(c);
		
		if (fabs(y) < eps)
		{
			ret = SUCCESS;
			break;
		} else if ((fabs(c - a) < DBL_EPSILON) || (fabs(c - b) < DBL_EPSILON))
		{
			ret = HIGH_ERROR;
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
	
	if (it >= m)
		ret = RUN_TIME;
	
	*x = c;
	*m_it = it;

	return ret;
}

