#ifndef SOLVE_H
#define SOLVE_H

double t11_solve (
		double (*f) (double), 
		double a, double eps, 
		double *res
);

#endif
