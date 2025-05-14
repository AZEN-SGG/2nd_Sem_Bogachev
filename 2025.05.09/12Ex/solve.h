#ifndef SOLVE_H
#define SOLVE_H

int t12_solve (
		double (*x) (double), 
		double (*y) (double),
		double a, double b,
		double eps, double *res
);

#endif
