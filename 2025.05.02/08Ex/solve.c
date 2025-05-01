#include "solve.h"
#include "status.h"

#include <math.h>
#include <float.h>


int t8_solve (
		double (*f) (double), 
		double a, double b, 
		double eps, int m, double *x
) {
	int it = 0;
	status ret = SUCCESS;
	double c = DBL_MAX, y, y_a = f(a), y_b = f(b);

	if (fabs(y_a) - eps < DBL_EPSILON)
	{
		*x = a;
		return SUCCESS;
	} if (fabs(y_b) - eps < DBL_EPSILON)
	{
		*x = b;
		return SUCCESS;
	} if (fabs(fabs(y_b) - fabs(y_a)) < DBL_EPSILON)
	{
		*x = a;
		return EQUAL;
	}

	for (it = 0; it < m; ++it)
	{
		double h = (b - a) * 0.1;
		c = a + h;
		y = f(c);
		
		if (fabs(y) - eps < DBL_EPSILON)
		{
			ret = SUCCESS;
			break;
		} else if (fabs(y_a) - fabs(y_b) > DBL_EPSILON)
		{
			a = c;
			y_a = y;
		} else if (fabs(y_b) - fabs(y_a) > DBL_EPSILON)
		{
			b = c;
			y_b = y;
		} else
		{
			ret = EQUAL;
			break;
		}
	}
	
	if (it >= m)
		ret = RUN_TIME;
	
	*x = c;
	*m_it = it;

	return ret;
}

