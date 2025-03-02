#include "solve.h"

int check(char **a, int n, int (*cmp)(const char *, const char *))
{
	/* Каждый элемент больше следующего */
	int i; int count = 0;
	for (i = 1; i < n; i++)
	{
		if ((*cmp)(a[i-1], a[i]) > 0)
			count++;
	}
	return count;
}
