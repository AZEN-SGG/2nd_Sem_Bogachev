#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "io_status.h"
#include "array.h"
#include "solve.h"

int main(int argc, char * argv[]) {
	int task = 7;
	int n = 0, m = 0;
	char * name = 0;
	char * s = 0;
	char ** a = 0;
	io_status res;
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
	res = read_array(a, n, name);
	do {
		switch (res) {
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
	res = t7_solve(a, n, s);
	t = (clock() - t);
	printf("New array:\n");
	print_array(a, res, m);
	printf("%s : Task = %d Result = %d Elapsed = %.2f\n",
			argv[0], task, res, t);
	free_array(a, res);
	free(a);
	a = 0;
	return 0;
}
