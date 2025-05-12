#ifndef SOLVE_H
#define SOLVE_H

#define NUM_FPE 1e-300

double t5_solve (
		double (*f) (double), 
		double a, double b,
		int n	
);

#endif
