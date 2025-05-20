#include <stdio.h>
#include <time.h>
#include <math.h>
#include <float.h>

#include "solve.h"
#include "node.h"
#include "io_node.h"
#include "status.h"

/* ./a10.out p filename */
int main (int argc, char *argv[])
{
	node *head = NULL;
	char *name;
	double t;
	int p, len, task = 10;
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

	fprintf (stdout, "Source list:\n");
	print_list(head, p);
	
	t = clock();
	head = t10_solve(head);
	t = (clock() - t) / CLOCKS_PER_SEC;
	
	fprintf (stdout, "\nFinal list:\n");
	print_list(head, p);
	len = get_length(head);

	delete_list(head);

	fprintf (stdout, "%s : Task = %d Length = %d Elapsed = %.2f\n", argv[0], task, len, t);
	return 0;
}

