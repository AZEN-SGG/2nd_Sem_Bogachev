#ifndef ARRAY_IO_H
#define ARRAY_IO_H

int init_array (
		double (*f) (double), 
		double *d, int m,
		double a, double b,
	       	double eps, double *ret
);

#endif
