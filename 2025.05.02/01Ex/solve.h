#ifndef SOLVE_H
#define SOLVE_H

int t1_solve (
		double (*f) (double), 
		double a, double b, 
		double eps, int m, double *x
		);

#endif
