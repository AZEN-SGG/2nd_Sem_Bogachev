#include "solve.h"
#include "status.h"

#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

int t9_solve (
		double (*f) (double), 
		double a, double b, 
		double eps, int m, double *x
) {
	int it = 0;
	double c = DBL_MAX, y, y_a = f(a), y_b = f(b);

	if (fabs(y_a) - eps < DBL_EPSILON)
	{
		*x = a;
		return SUCCESS;
	} if (fabs(y_b) - eps < DBL_EPSILON)
	{
		*x = b;
		return SUCCESS;
	}

	if (sgn_a == sgn_b)
	{
		*x = DBL_MAX;
		return MORE_ONE_ROOT;
	}
	
	for (it = 0; it < m; ++it)
	{
		c = (a + b) * 0.5;
		y = f(c);
		
		memcpy(&bits, &y, sizeof(bits));
		sgn_c = (bits >> 63) & 1;
		
		if (fabs(y) - eps < DBL_EPSILON)
		{
			ret = SUCCESS;
			break;
		} else if ((fabs(c - a) < DBL_EPSILON) || (fabs(c - b) < DBL_EPSILON))
		{
			ret = HIGH_ERROR;
			break;
		} else if (sgn_c == sgn_a)
		{
			a = c;
			y_a = y;
		} else if (sgn_c == sgn_b)
		{
			b = c;
			y_b = y;
		}
	}
	
	if (it >= m)
		ret = RUN_TIME;
	
	*x = c;

	return ret;
}

