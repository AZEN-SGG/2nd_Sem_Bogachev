#include "solve.h"
#include "node.h"
#include "io_node.h"

#include <string.h>
#include <stdlib.h>

node * t10_solve (node *head)
{
	int down = 0;
	node *last, *curr, *next,
		*start;
	last=next=start=NULL;
	curr = head;

	for (next=curr->next; next; next=curr->next)
	{
		if (strcmp(next->string, curr->string) <= 0) {
			if (!down)
				start = last;
			down++;
		} else {
			if (down) {
				if (start) {
					delete_nodes(start->next, down+1);
					start->next = next;
					curr = start;
				} else {
					delete_nodes(head, down+1);
					head = next;
					curr = NULL;
				}
			}
			down = 0;
		}
		
		last = curr;
		curr = next;
	}

	if (down) {
		if (start) {
			delete_nodes(start->next, down+1);
			start->next = NULL;
		} else {
			delete_nodes(head, down+1);
			head = NULL;
		}
		curr = NULL;
		last = NULL;
	}

	return head;
}

