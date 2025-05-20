#include "solve_03.h"
#include "node.h"

#include <string.h>

int t3_solve (node *head)
{
	node *next = NULL;
	int count = 0, local = 0;
	
	if (!head)
		return 0;

	for (next = head->next; next; next = head->next)
	{
		int cmp = strcmp(next->string, head->string);
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

		head = next;
	}

	return count;
}

