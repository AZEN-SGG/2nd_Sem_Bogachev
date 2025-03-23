#include "init_f.h"
#include <math.h>

#define MAX(n, m) (n < m ? m : n)

double f1(int n, int m, int i, int j)
{
	return MAX(n, m) - MAX(i, j) + 1;
}

double f2(int n, int m, int i, int j)
{
	(void)n;
	(void)m;
	return MAX(i, j);
}

double f3(int n, int m, int i, int j)
{
	(void)n;
	(void)m;
	return abs(i - j);
}

double f4(int n, int m, int i, int j)
{
	(void)n;
	(void)m;
	return 1./(i+j-1);
}
