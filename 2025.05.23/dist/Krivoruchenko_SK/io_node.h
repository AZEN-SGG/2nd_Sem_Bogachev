#ifndef IO_NODE_H
#define IO_NODE_H

#include "node.h"
#include "status.h"

#include <stdlib.h>

static inline void delete_node (node *head)
{
	free(head->string);
	free(head);
}

int get_length (node *head);
void delete_nodes (node *head, const int count);
void delete_list (node *head);
io_status read_list (node **list, const char *filename);
void print_list (node *head, const int p);

#endif
