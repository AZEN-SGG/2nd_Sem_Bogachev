#include "solve_03.h"
#include "node.h"

#include <string.h>

int t3_solve (node *head)
{
	char *last = head->string;
	int count = 0, local = 1;

	for (head = head->next; head; head = head->next)
	{
		int cmp = strcmp(head->string, last);
		if (cmp < 0) {
			if (local) {
				count += local;
				local = 0;
			}
		} else if (cmp == 0) {
			if (local)
				local++;
		} else
			local = 1;

		last = head->string;
	}

	count += local;

	return count;
}

