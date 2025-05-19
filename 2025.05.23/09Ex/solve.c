#include "solve.h"
#include "node.h"
#include "io_node.h"

#include <string.h>
#include <stdlib.h>

node * t9_solve (node *head)
{
	node *last, *curr = head, *next, 
	     *deleted = NULL, *last_cmp;
	int cmp;

	next = head->next;
	if (!next)
		return head;

	cmp = strcmp(curr->string, next->string);
	if (cmp >= 0) {
		deleted = curr;

		head = next;
		curr = next;
		next = next->next;

		if (!next) {
			delete_node(deleted);
			if (cmp == 0)
				delete_node(curr);
			return NULL;
		}
	}

	for (next = curr->next; next->next;)
	{
		last_cmp = curr;

		last = curr;
		curr = next;
		next = curr->next;

		if (deleted)
			last_cmp = deleted;

		if (
				(strcmp(curr->string, next->string) >= 0) && 
				(strcmp(curr->string, last_cmp->string) >= 0) 
		) {
			if (deleted)
				delete_node(deleted);
			deleted = curr;

			last->next = next;
			curr = last;
		} else {
			if (deleted)
				delete_node(deleted);
			deleted = NULL;
		}
	}

	if (deleted)
		last_cmp = deleted;
	else
		last_cmp = curr;

	if (strcmp(next->string, last_cmp->string) >= 0) {
		curr->next = NULL;

		delete_node(next);
	}

	if (deleted)
		delete_node(deleted);

	return head;
}

