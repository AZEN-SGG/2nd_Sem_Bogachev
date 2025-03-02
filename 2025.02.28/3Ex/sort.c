#include "sort.h"

int up_strcmp(const char *a, const char *b)
{ return strcmp(a, b); }

int down_strcmp(const char *a, const char *b)
{ return -strcmp(a, b); }

int up_len(const char *a, const char *b)
{
	int i = 0;
	while (1)
	{
		if (a[i] == '\0' && b[i] == '\0') return strcmp(a, b);
		else if (a[i] == '\0') return -1;
		else if (b[i] == '\0') return 1;

		i++;
	}
}
int down_len(const char *a, const char *b)
{ return -up_len(a, b); }

