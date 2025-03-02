#include "compare.h"

int up_strcmp(const char *a, const char *b)
{ return strcmp(a, b); }

int down_strcmp(const char *a, const char *b)
{ return strcmp(b, a); }

int up_len(const char *a, const char *b)
{
	ssize_t diff = (ssize_t)strlen(a) - (ssize_t)strlen(b);
	if (diff < 0) return -1;
	if (diff > 0) return 1;
	return up_strcmp(a, b);
}

int down_len(const char *a, const char *b)
{ return up_len(b, a); }
