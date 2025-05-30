#ifndef IO_NODE_H
#define IO_NODE_H

#include "node.h"
#include "status.h"

int get_length (node * head);
void delete_list (node * head);
io_status read_list (node **list, const char *filename);
void print_list (node *head, const int p);

#endif
