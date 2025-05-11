#ifndef SOLVE_H
#define SOLVE_H

#define NUM_FPE 1e-300

double t3_solve (
		double (*f) (double), 
		double x, double h 
);

#endif
