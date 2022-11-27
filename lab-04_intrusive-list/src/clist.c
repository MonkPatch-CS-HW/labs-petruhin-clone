#include <stdlib.h>
#include "clist.h"

void init_list(intrusive_list_t *list)
{
  list->head = malloc(sizeof(intrusive_node_t));
  list->head->next = NULL;
  list->head->prev = NULL;
}

void uninit_list(intrusive_list_t *list)
{
  free(list->head);
}

void add_node(intrusive_list_t *list, intrusive_node_t *node)
{
  if (!list->head)
    init_list(list);
  node->next = list->head->next;
  node->prev = list->head;
  if (list->head->next)
    list->head->next->prev = node;
  list->head->next = node;
}

void remove_node(intrusive_node_t *node)
{
  if (node->next)
    node->next->prev = node->prev;
  if (node->prev)
    node->prev->next = node->next;
}

int get_length(intrusive_list_t *list)
{
  intrusive_node_t *current = list->head;
  int length = 0;
  while ((current = current->next))
    length++;
  return length;
}