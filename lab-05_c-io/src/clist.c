#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
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

int try_insert_first_node(intrusive_list_t *list, intrusive_node_t *node)
{
  if (!list->head)
    init_list(list);

  if (list->head->next || list->head->prev)
    return -1;

  list->head->next = node;
  list->head->prev = node;

  node->next = NULL;
  node->prev = NULL;

  return 0;
}

void add_node_back(intrusive_list_t *list, intrusive_node_t *node)
{
  if (try_insert_first_node(list, node) == 0)
    return;

  node->prev = list->head->prev;
  node->next = NULL;

  node->prev->next = node;
  list->head->prev = node;
}

void add_node(intrusive_list_t *list, intrusive_node_t *node)
{
  if (try_insert_first_node(list, node) == 0)
    return;

  node->next = list->head->next;
  node->prev = NULL;

  node->next->prev = node;
  list->head->next = node;
}

void remove_node(intrusive_list_t *list, intrusive_node_t *node)
{
  intrusive_node_t *current = list->head;
  while ((current = current->next) && current != node)
    ;
  if (!current)
    return;
  if (list->head->next == node)
    list->head->next = node->next;
  if (list->head->prev == node)
    list->head->prev = node->prev;
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

void apply(intrusive_list_t *list, void (*op)(intrusive_node_t *node, void *data), void *data)
{
  intrusive_node_t *current = list->head;
  while ((current = current->next))
    op(current, data);
}
