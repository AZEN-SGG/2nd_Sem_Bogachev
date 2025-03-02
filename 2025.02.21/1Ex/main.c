#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "io_status.h"
#include "array.h"
#include "solve.h"

int main(int argc, char * argv[]) {
	int task = 1;
	int n = 0, m = 0;
	char * name = 0;
	char * s = 0;
	char ** a = 0;
	io_status ret;
	double t;

	if (!(argc == 5 && sscanf(argv[1], "%d", &n) == 1 && sscanf(argv[2], "%d", &m) == 1))
	{
		printf("Usage: %s n m file string\n", argv[0]);
		return 1;
	}
	name = argv[3];
	s = argv[4];
	a = (char **)malloc(n * sizeof(char **));
	if (!a) 
	{
		printf("Can not allocate array len %d\n", n);
		return ERROR_MEM;
	}
	ret = read_array(a, n, name);
	do {
		switch (ret) {
			case SUCCESS:
				continue;
			case ERROR_OPEN:
				printf("Can not open %s\n", name);
				break;
			case ERROR_READ:
				printf("Can not read %s\n", name);
				break;
			case ERROR_MEM:
				printf("Not enough memory\n");
				break;
		}

		free(a);
		return 3;
	} while (0);

	print_array(a, n, m);
	t = clock();
	ret = t1_solve(a, n, s);
	t = (clock() - t);
	printf("New array:\n");
	print_array(a, ret, m);
	printf("%s : Task = %d Result = %d Elapsed = %.2f\n",
			argv[0], task, ret, t);
	free_array(a, ret);
	free(a);
	a = 0;
	return 0;
}
