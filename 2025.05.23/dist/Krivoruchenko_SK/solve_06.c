#include "solve_06.h"
#include "node.h"

#include <string.h>

int t6_solve (node *head)
{
	char *last = head->string;
	int count = 0, local = 0;

	for (head = head->next; head; head = head->next)
	{
		if (strcmp(head->string, last) == 0)
			local = 1;
		else {
			count += local;
			local = 0;
		}
		last = head->string;
	}

	count += local;

	return count;
}

