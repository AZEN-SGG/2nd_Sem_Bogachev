#include "solve.h"
#include "node.h"

#include <string.h>

int t4_solve (node *head)
{
	int maximum = 0, count = 0, local = 0, strict = 0;
	node *last, *next;

	last = head;
	head = last->next;

	for (next = head->next; next; next = head->next)
	{
		int last_cmp = strcmp(head->string, last->string);
		
		if (last_cmp == 0) {
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

	return maximum;
}
/*
	char *last = head->string;
	int maximum = 0, count = 0, local = 0, strict = 0;

	for (head = head->next; head; head = head->next)
	{
		int cmp = strcmp(head->string, last);
		if (cmp > 0) {
			count += local;
			if (maximum < count)
				maximum = count;
			count = 0;
			local = 1;
			strict = 1;
		} else if (cmp < 0) {
			if (!strict)
				count += local;
			local = 1;
			strict = 0;
		} else {
			if (local)
				local++;
		}
		last = head->string;
	}
	
	return maximum;
}
*/
