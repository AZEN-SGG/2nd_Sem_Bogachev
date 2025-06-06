#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "io_status.h"
#include "list.h"

int solve6(node*);

int main(int argc, char* argv[])
  {
  int task = 6;
  char* name = 0;
  node* head = 0;
  io_status ret;
  int p;
  int res;
  double t;
  if (!(argc == 3 && sscanf(argv[1], "%d", &p) == 1))
      {
      printf("Usage: %s p file\n", argv[0]);
      return -1;
      }
  name = argv[2];
  ret = read_list(&head, name);
  if (ret != SUCCESS)
      {
      switch (ret)
          {
          case ERROR_OPEN:
              printf("Cannot open file %s\n", name);
              return -1;
          case ERROR_READ:
              printf("Cannot read file %s\n", name);
              return -2;
          case ERROR_MEM:
              printf("Cannot allocate memory\n");
              return -3;
          default:
              printf("Unknown error in file %s\n", name);
              return -4;
          }
      }
  print_list(head, p);
  t = clock();
  res = solve6(head);
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
  free_list(head);
  return 0;
  }

int solve6(node* head)
  {
  node* curr;
  node* prev = head;
  int count = 0, flag = 0;
  for (curr = head->next; curr; prev = curr, curr = curr->next)
      {
      if (strcmp(curr->string, prev->string) == 0) flag = 1;
      else
          {
          if (flag == 1) count++;
          flag = 0;
          }
      }
  if (flag == 1) count++;
  return count;
  }
