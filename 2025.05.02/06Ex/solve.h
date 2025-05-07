#ifndef SOLVE_H
#define SOLVE_H

int t6_solve (
		double (*f) (double), 
		const int m, double *d,
		double a, double b, 
		const double eps, const int M, double *res
);

#endif
