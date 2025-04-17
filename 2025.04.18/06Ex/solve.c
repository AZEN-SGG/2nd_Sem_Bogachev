#include "solve.h"
#include "contin_func.h"

#include <stdlib.h>
#include <math.h>
#include <float.h>

double fcos (double x, const double eps)
{
	double answer;
	short flag = 1;

	if (x - M_PI*2 >= DBL_EPSILON)
		x = fmod(x, M_PI*2);

	if (x - M_PI >= DBL_EPSILON)
	{
		x -= M_PI;
		flag *= -1;
	}

	if (x - 1 >= DBL_EPSILON)
	{
		x -= M_PI_2;
		flag *= -2;
	}

	if (abs(flag) == 2)
	{
		x /= 2;

		answer = ((flag > 0) - (flag < 0)) * (2 * ssin(x, eps) * scos(x, eps));
	} else
		answer = flag * scos(x, eps);

	return answer;
}


