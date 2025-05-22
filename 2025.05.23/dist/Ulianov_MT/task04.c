#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "io_status.h"
#include "list.h"

int solve4(node*);

int main(int argc, char* argv[])
  {
  int task = 4;
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
  res = solve4(head);
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, t);
  free_list(head);
  return 0;
  }
  
int solve4(node* head)
  {
  int i;
  int flag = 0;
  node* curr;
  node* prev = head;
  node* next;
  char* curr_str;
  char* next_str;
  char* prev_str;
  int begin = 0, max = 0, dist = 0;
  for (curr = head->next, next = curr->next, i = 0; next; prev = curr, curr = next, next = next->next, i++)
      {
      curr_str = curr->string;
      next_str = next->string;
      prev_str = prev->string;
      if (strcmp(curr_str, prev_str) >= 0 && strcmp(curr_str, next_str) >= 0)
          {
          if (flag)
              {
              dist = i - begin - 1;
              if (dist > max) max = dist;
              begin = i;
              }
          else
              {
              flag = 1;
              begin = i;
              }
          }
      }
  return max;
  }
