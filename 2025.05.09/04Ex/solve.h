#ifndef SOLVE_H
#define SOLVE_H

#define NUM_FPE 1e-300

double t4_solve (
		double (*f) (double), 
		double a, double b,
		int n	
);

#endif
