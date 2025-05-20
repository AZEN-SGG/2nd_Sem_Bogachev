#include "solve.h"
#include "node.h"

#include <string.h>

int t3_solve (node *head)
{
	node *last, *next = NULL;
	int count = 0, local = 0;
	
	if (!head)
		return 0;
	
	last = head;
	head = last->next;

	if (!head)
		return 0;

	for (next = head->next; next; next = head->next)
	{
		int cmp_last = strcmp(head->string, last->string);
		int cmp_next = strcmp(head->string, next->string);

		if (cmp_last > 0) {
			local = 1;
		} else if (cmp_last == 0) {
			if (local) {
				if (cmp_next < 0) {
					count += local;
					local = 0;
				} else
					local++;
			}
		} else {
			count += local;
			local = 0;
		}
		
		last = head;
		head = next;
	}

	if (strcmp(last->string, head->string) >= 0)
		count += local;
	else
		if (local >= 1)
			count += local - 1;
	
	return count;
}

