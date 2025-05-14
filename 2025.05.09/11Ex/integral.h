#ifndef INTEGRAL_H
#define INTEGRAL_H

int simpson (
		double (*f) (double), 
		double a, double b,
		double eps, double *res
);

#endif
