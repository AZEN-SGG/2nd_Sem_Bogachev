#include "solve_08.h"
#include "node.h"

#include <string.h>
#include <stdlib.h>

node * t8_solve (node *head)
{
	node *last = head;
	node *curr, *next;
	
	curr = head->next;
	if (!curr)
		return head;

	while (strcmp(last->string, curr->string) >= 0) {
		free(last->string);
		free(last);

		last = curr;
		head = curr;
		curr = curr->next;
		if (!curr)
			return head;
	}

	for (next = curr->next; next; next = curr->next)
	{
		if (strcmp(curr->string, next->string) >= 0) {
			free(curr->string);
			free(curr);
			
			last->next = next;
		} else
			last = curr;

		curr = next;
	}

	return head;
}

