#include "solve.h"
#include "contin_func.h"

#include <stdlib.h>
#include <math.h>
#include <float.h>

double fsin (double x, const double eps)
{
	double answer;
	short flag = 1;

	if (-x > DBL_EPSILON)
	{
		x = -x;
		flag = -1;
	}
	
	if (x - M_PI*2 >= DBL_EPSILON)
		x = fmod(x, M_PI*2);

	if (x - M_PI >= DBL_EPSILON)
	{
		x -= M_PI;
		flag *= -1;
	}

	if (x - M_PI_2 >= DBL_EPSILON)
	{
		x -= M_PI_2;
		flag *= 2;
	}

	if (abs(flag) == 2)
	{
		double cosinus, sinus;
		x /= 2;

		cosinus = scos(x, eps);
		sinus = ssin(x, eps);

		answer = ((flag > 0) - (flag < 0)) * (cosinus * cosinus - sinus * sinus);
	} else
		answer = flag * ssin(x, eps);

	return answer;
}


