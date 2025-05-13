#ifndef SOLVE_H
#define SOLVE_H

#define NUM_FPE 1e-300

#include "init_f.h"

#include <stddef.h>

double t1_solve (
		double (*f) (double), 
		double x, double h 
);

// -------

double t2_solve (
		double (*f) (double), 
		double x, double h 
);

// -------

double t3_solve (
		double (*f) (double), 
		double x, double h 
);

// -------

double t4_solve (
		double (*f) (double), 
		double a, double b,
		int n	
);

// -------

double t5_solve (
		double (*f) (double), 
		double a, double b,
		int n	
);

// -------

static double (*f_global)(double) = NULL;

static inline double wf (double x)
{
		return f_global(x) * weight(x);
}

double t6_solve (
		double (*f) (double), 
		double a, double b,
		int n	
);

// -------

double t7_solve (
		double (*f) (double), 
		double a, double b,
		int n	
);

// -------

#endif
