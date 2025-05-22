#include "solve.h"
#include "node.h"

#include <string.h>

int t4_solve (node *head)
{
	int maximum = 0, count = 0, local = 0, strict = 0;
	node *last, *next;

	last = head;
	head = last->next;
	
	if (!head)
		return 0;

	for (next = head->next; next; next = head->next)
	{
		int last_cmp = strcmp(head->string, last->string);
		
		if (last_cmp == 0) {
			if (strict) {
				if (maximum < count)
					maximum = count;
				count = 0;
				local = 1;
			} else 
				local += (local > 0);
		} else if (last_cmp < 0) {
			if (strict) {
				if (maximum < count)
					maximum = count;
				count = 0;
				local = 1;
			} else
				local += (local > 0);
			strict = 0;
		} else {
			count += local;
			local = (local > 0);

			strict = 1;
		}

		last = head;
		head = next;
	}
	
	if (strcmp(head->string, last->string) <= 0)
			if (strict)
				if (maximum < count)
					maximum = count;

	return maximum;
}

