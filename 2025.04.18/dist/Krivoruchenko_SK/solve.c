#include "solve.h"
#include "contin_func.h"

#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include <math.h>

// the Lagrange interpolation polynomial
double t1_solve (const double x_0, const int n, const double * restrict X, const double * restrict Y)
{
	double value = 0;

	for (int i = 0; i < n; ++i)
	{
		double x_i = X[i];
		double y_i = Y[i];
		
		double numerator = y_i;
		double denominator = 1;

		if (fabs(x_0 - x_i) < DBL_EPSILON)
			return y_i;

		for (int j = 0; j < i; ++j)
		{
			double x_j = X[j];
			numerator *= (x_0 - x_j);
			denominator *= (x_i - x_j);
		}

		for (int j = i+1; j < n; ++j)
		{
			double x_j = X[j];
			numerator *= (x_0 - x_j);
			denominator *= (x_i - x_j);
		}

		if (fabs(denominator) < DBL_EPSILON)
			return DBL_MAX;
		
		value += numerator / denominator;
	}

	return value;
}

// the Newton interpolation polynomial
double t2_solve (const double x_0, const int n, const double * restrict X, double * restrict Y)
{
	double value, start_value;

	for (int k = 0; k < n-1; ++k)
	{
		double last_x; 
		double last_y = Y[n-1];
		
		for (int i = n-2; i >= k; --i)
		{
			const double x_i = X[i-k];
			const double y_i = Y[i];
			last_x = X[i+1];
			
			if (fabs(last_x - x_i) < DBL_EPSILON)
				return DBL_MAX;
			
			Y[i+1] = (last_y - y_i) / (last_x - x_i);

			last_y = y_i;
		}
	}

	start_value = 1;
	value = 0;

	for (int i = 0; i < n; ++i)
	{
		value += Y[i] * start_value;
		start_value *= (x_0 - X[i]);
	}

	return value;
}

// Interpolation polynomial according to Aitken's scheme
double t3_solve (const double x_0, const int n, const double * restrict X, double * restrict Y)
{
	for (int k = 0; k < n-1; ++k)
	{
		double x_j; 
		double y_j = Y[n-1];
		
		for (int i = n-2; i >= k; --i)
		{
			const double x_i = X[i-k];
			const double y_i = Y[i];
			x_j = X[i+1];
			
			if (fabs(x_j - x_i) < DBL_EPSILON)
				return DBL_MAX;
			
			Y[i+1] = ((x_0-x_i) * y_j - (x_0-x_j) * y_i) / (x_j - x_i);

			y_j = y_i;
		}
	}

	return Y[n-1];
}

// Newton's interpolation polynomial with derivative
double t4_solve (
		const double x_0, const int n, 
		const double * restrict X, 
		double * restrict Y,
		double * restrict D
		)
{
	double value, start_value;
	double x_j = X[n-1];
	double y_j = Y[n-1];

	for (int i = n-2; i >= 0; --i)
	{
		const double x_i = X[i];
		const double y_i = Y[i];
		
		if (fabs(x_j - x_i) < DBL_EPSILON)
			return DBL_MAX;
		
		Y[i+1] = (y_j - y_i) / (x_j - x_i);

		y_j = y_i;
		x_j = x_i;
	}

	for (int k = 1; k < n*2-1; ++k)
	{
		double f_j = D[n-1];

		for (int l = n*2-2; l >= k; --l)
		{
			const int i = l >> 1;
			double x_i, f_i, *f;
			
			if (l & 1)
			{
				x_i = X[i-(k>>1)];

				f_i = D[i];
				f = Y + i + 1;
			} else 
			{
				x_j = X[i];
				x_i = X[i-(k>>1)-(k&1)];

				f_i = Y[i];
				f = D + i;
			}

			if (fabs(x_j - x_i) < DBL_EPSILON)
				return DBL_MAX;
			
			*f = (f_j - f_i) / (x_j - x_i);
			f_j = f_i;	
		}
	}

	start_value = 1;
	value = 0;

	for (int i = 0; i < n; ++i)
	{
		const double diff = (x_0 - X[i]);

		value += Y[i] * start_value;
		start_value *= diff;

		value += D[i] * start_value;
		start_value *= diff;
	}

	return value;
}

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

double fexp (double x, const double eps)
{
	double integral, fractal, answer = 1;
	bool is_negative = false;

	if (x < DBL_EPSILON)
	{
		is_negative = true;
		x = -x;
	}

	integral = floor(x);
	fractal = x - integral;

	for (double i = 0; (integral - i) > DBL_EPSILON; ++i)
		answer *= M_E;

	answer *= sexp(fractal, eps);
	if (is_negative)
		answer = 1. / answer;

	return answer;
}

double dln (double x, const double eps)
{
	double value = 0;
	int b = 0;

	while (x - 2 > DBL_EPSILON)
	{
		x *= 0.5;
		b++;
	}
	
	while (x - 1 <= DBL_EPSILON)
	{
		x *= 2;
		b--;
	}
	
	value = fln(x, eps);

	value += b * M_LN2;
	return value;
}
