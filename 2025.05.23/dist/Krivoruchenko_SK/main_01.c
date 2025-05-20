#include <stdio.h>
#include <time.h>
#include <math.h>
#include <float.h>

#include "solve_01.h"
#include "node.h"
#include "io_node.h"
#include "status.h"

/* ./a01.out p filename */
int main (int argc, char *argv[])
{
	node *head = NULL;
	char *name;
	double t;
	int p, res, task = 1;
	io_status ret;

	if (
			!((argc == 3) && 
			sscanf(argv[1], "%d", &p) == 1 &&
			argv[2])
	) {
		fprintf(stderr, "Usage: %s p filename\n", argv[0]);
		return -1;
	}

	name = argv[2];

	ret = read_list(&head, name);
	do {
		switch (ret) {
			case SUCCESS:
				continue;
			case ERR_OPEN:
				fprintf (stderr, "%s '%s'!\n", ERR_MSG_OPEN, name);
				break;
			case ERR_READ:
				fprintf (stderr, "%s '%s'!\n", ERR_MSG_READ, name);
				break;
			case ERR_MEM:
				fprintf (stderr, "%s!\n", ERR_MSG_MEM);
				break;
		}

		delete_list(head);
		return -2;
	} while (0);	

	print_list(head, p);

	t = clock();
	res = t1_solve(head);
	t = (clock() - t) / CLOCKS_PER_SEC;
	
	delete_list(head);

	if (res < 0) {
		fprintf (stderr, "%s : Task = %d Undefined error Elapsed = %.2f\n", argv[0], task, t);
		return -3;
	} else {
		fprintf (stdout, "%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
		return 0;
	}
}

