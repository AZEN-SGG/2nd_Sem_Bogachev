#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io_status.h"
#include "list.h"

io_status read_list(node** head, char* name)
  {
  char buf[LEN];
  FILE *fp;
  int j;
  node* curr;
  node* prev;
  if (!(fp = fopen(name, "r"))) return ERROR_OPEN;
  curr = (node*) malloc(sizeof(node));
  if (!curr)
      {
      fclose(fp);
      return ERROR_MEM;
      }
  curr->next = 0;
  if (!fgets(buf, LEN, fp))
      {
      fclose(fp);
      free(curr);
      return ERROR_READ;
      }
  for (j = 0; buf[j]; j++)
      {
      if (buf[j] == '\n')
          {
          buf[j] = '\0';
          break;
          }
      }
  curr->string = (char*) malloc((j + 1) * sizeof(char));
  if (!curr->string)
      {
      fclose(fp);
      free_list(curr);
      return ERROR_MEM;
      }
  strcpy(curr->string, buf);
  *head = curr;
  prev = curr;
  while (fgets(buf, LEN, fp))
      {
      for (j = 0; buf[j]; j++)
          {
          if (buf[j] == '\n')
              {
              buf[j] = '\0';
              break;
              }
          }
      curr = (node*) malloc(sizeof(node));
      if (!curr) 
          {
          fclose(fp);
          free_list(*head);
          return ERROR_MEM;
          }
      curr->next = 0;
      curr->string = (char*) malloc((j + 1) * sizeof(char));
      if (!curr->string)
          {
          free_list(*head);
          fclose(fp);
          return ERROR_MEM;
          }
      strcpy(curr->string, buf);
      prev->next = curr;
      prev = curr;
      }
  if (!feof(fp))
      {
      fclose(fp);
      free_list(*head);
      return ERROR_READ;
      }
  fclose(fp);
  return SUCCESS;
  }

void print_list(node* head, int p)
  {
  int i = 0;
  node* curr;
  for (curr = head; curr; curr = curr->next) 
      {
      if (i >= p) break;
      printf("%s\n", curr->string);
      i++;
      }
  }

void free_list(node* head)
  {
  node* curr;
  node* next;
  for (curr = head; curr; curr = next)
      {
      next = curr->next;
      free(curr->string);
      free(curr);
      }
  }
  
int get_length(node* head)
  {
  node* curr;
  int len = 0;
  for (curr = head; curr; curr = curr->next) len++;
  return len;
  }
