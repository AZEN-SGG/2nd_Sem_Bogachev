#include "init_f.h"
#include <stdlib.h>

#define MAX(n, m) (n < m ? m : n)

double f1(int m, int n, int i, int j)
{
	return MAX(n, m) - MAX(i, j) + 1;
}

double f2(int m, int n, int i, int j)
{
	(void)n;
	(void)m;
	return MAX(i, j);
}

double f3(int m, int n, int i, int j)
{
	(void)n;
	(void)m;
	return abs(i - j);
}

double f4(int m, int n, int i, int j)
{
	(void)n;
	(void)m;
	return 1./(i+j-1);
}
