#ifndef SOLVE_H
#define SOLVE_H

int t2_solve (
		double (*f) (double), 
		double (*d) (double), 
		double x_0, double eps, 
		int m, double *x
		);

#endif
