#ifndef SOLVE_H
#define SOLVE_H

int t8_solve (
		double (*f) (double), 
		double a, double b,
		double eps, double *res
);

#endif
