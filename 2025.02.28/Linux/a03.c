#include "solve.h"
#include "sort.h"
#include "array.h"
#include "io_status.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
	/* ./aout x c n p filename */
	int c, p, n, res, task = 3;
	io_status ret;
	char *name, *x, **a;
	int (*cmp)(const char *, const char *);
	int (*f[])(const char *, const char *) = {up_strcmp, down_strcmp, up_len, down_len};
	int len_f = sizeof(f) / sizeof(f[0]);
	double t;

	if (!(argc == 6 && sscanf(argv[2], "%d", &c) && sscanf(argv[3], "%d", &n) == 1 && sscanf(argv[4], "%d", &p) == 1 && c >= 1 && c <= len_f))
	{
		printf("Usage %s x c n p name\n", argv[0]);
		return 1;
	}
	x = argv[1];
	name = argv[5];
	cmp = f[c-1];

	if (!(a = (char **)malloc(n * sizeof(char *))))
	{
		printf("Not enough memory: \n");
		return 2;
	}
	ret = read_array(a, n, name);

	do {
		switch(ret)
		{
			case SUCCESS:
				continue;
			case ERROR_OPEN:
				printf("Cannot open %s\n", name);
				break;
			case ERROR_READ:
				printf("Cannot read %s\n", name);
				break;
			case ERROR_MEM:
				printf("Not enough memory");
				break;
		}
			free(a);
			return 3;
	} while (0);
	
	print_array(a, n, p);
	t = clock();
	res = t3_solve(a, n, x, cmp);
	t = (clock() - t) / CLOCKS_PER_SEC;

	printf("New array:\n");
	print_array(a, n, p);
	printf("%s : Task = %d Res = %d Elapsed = %.2f\n", argv[0], task, res, t);
	
	free_array(a, n);
	free(a);

	return 0;
}
