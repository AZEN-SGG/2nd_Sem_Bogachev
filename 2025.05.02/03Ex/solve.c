#include "solve.h"
#include "status.h"

#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

status t3_solve (
		double (*f) (double), 
		double a, double b, 
		double eps, int m, double *x, int *m_it
) {
	int it = 0;
	uint64_t bits;
	status ret = SUCCESS;
	double c = DBL_MAX, y, y_a = f(a), y_b = f(b);
	bool sgn_a, sgn_b, sgn_c;

	memcpy(&bits, &y_a, sizeof(bits));
	sgn_a = (bits >> 63) & 1;
	memcpy(&bits, &y_b, sizeof(bits));
	sgn_b = (bits >> 63) & 1;

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
		c = a - ((a - b) / (y_a - y_b)) * y_a;
		y = f(c);
		
		memcpy(&bits, &y, sizeof(bits));
		sgn_c = (bits >> 63) & 1;
		
		if ((c - a < DBL_EPSILON) || (c - b > DBL_EPSILON))
		{
			ret = BOUNDARIES;
			break;
		} else if (fabs(y) - eps < DBL_EPSILON)
		{
			ret = SUCCESS;
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
	*m_it = it;

	return ret;
}

