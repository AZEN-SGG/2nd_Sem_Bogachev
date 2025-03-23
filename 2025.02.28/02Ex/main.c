#include "solve.h"
#include "sort.h"
#include "array.h"
#include "io_status.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
	/* ./a02.out c n p_a filename_a m p_b filename_b */
	int c, p_a, n, p_b, m, diff, task = 2;
	io_status ret;
	char *name_a, *name_b, **arr_a, **arr_b, **arr_c;
	int (*cmp)(const char *, const char *);
	int (*f[])(const char *, const char *) = {up_strcmp, down_strcmp, up_len, down_len};
	int len_f = sizeof(f) / sizeof(f[0]);
	double t;

	if (!(argc == 8 && sscanf(argv[1], "%d", &c) && sscanf(argv[2], "%d", &n) == 1 && sscanf(argv[3], "%d", &p_a) == 1 && sscanf(argv[5], "%d", &m) && sscanf(argv[6], "%d",&p_b) && c >= 1 && c <= len_f))
	{
		printf("Usage %s c n p_a filename_a m p_b filename_b\n", argv[0]);
		return 1;
	}
	name_a = argv[4];
	name_b = argv[7];
	cmp = f[c-1];

	if (!(arr_a = (char **)malloc(n * sizeof(char *))))
	{
		printf("Not enough memory: \n");
		return 2;
	}
	if (!(arr_b = (char **)malloc(m * sizeof(char *))))
	{
		free(arr_a);

		printf("Not enough memory: \n");
		return 2;
	}
	if (!(arr_c = (char **)malloc((n+m) * sizeof(char *))))
	{
		free(arr_a);
		free(arr_b);

		printf("Not enough memory: \n");
		return 2;
	}


	ret = read_array(arr_a, n, name_a);

	do {
		switch(ret)
		{
			case SUCCESS:
				continue;
			case ERROR_OPEN:
				printf("Cannot open %s\n", name_a);
				break;
			case ERROR_READ:
				printf("Cannot read %s\n", name_a);
				break;
			case ERROR_MEM:
				printf("Not enough memory");
				break;
		}
			free(arr_a);
			free(arr_b);
			free(arr_c);
			return 3;
	} while (0);

	ret = read_array(arr_b, m, name_b);

	do {
		switch(ret)
		{
			case SUCCESS:
				continue;
			case ERROR_OPEN:
				printf("Cannot open %s\n", name_b);
				break;
			case ERROR_READ:
				printf("Cannot read %s\n", name_b);
				break;
			case ERROR_MEM:
				printf("Not enough memory");
				break;
		}
			free_array(arr_a, n);

			free(arr_a);
			free(arr_b);
			free(arr_c);
			return 3;
	} while (0);
	
	print_array(arr_a, n, p_a);
	printf("\n");
	print_array(arr_b, m, p_b);

	t = clock();
	t2_solve(arr_a, arr_b, arr_c, n, m, cmp);
	t = (clock() - t) / CLOCKS_PER_SEC;
	diff = check(arr_c, n+m, cmp);

	printf("New array:\n");
	print_array(arr_c, n+m, p_a+p_b);
	printf("%s : Task = %d Diff = %d Elapsed = %.2f\n", argv[0], task, diff, t);

	free_array(arr_a, n);
	free_array(arr_b, m);

	free(arr_a);
	free(arr_b);
	free(arr_c);

	return 0;
}
