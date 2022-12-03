#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clist.h"
#include "point_list.h"


void add_point(intrusive_list_t *list, int x, int y)
{
  point_t *point = malloc(sizeof(point_t));
  point->x = x;
  point->y = y;

  add_node(list, &point->node);
}

void add_point_back(intrusive_list_t *list, int x, int y)
{
  point_t *point = malloc(sizeof(point_t));
  point->x = x;
  point->y = y;

  add_node_back(list, &point->node);
}

void remove_point(intrusive_list_t *list, int x, int y)
{
  intrusive_node_t *current = list->head;
  while (current->next)
  {
    point_t *point = container_of(current->next, point_t, node);
    if (point->x != x || point->y != y)
    {
      current = current->next;
      continue;
    }
    remove_node(list, current->next);
    free(point);
  }
}

void show_all_points(intrusive_list_t *list)
{
  intrusive_node_t *current = list->head;
  while ((current = current->next))
  {
    point_t *point = container_of(current, point_t, node);
    printf("(%d %d)", point->x, point->y);
    if (current->next)
      printf(" ");
  }
  printf("\n");
}

void remove_all_points(intrusive_list_t *list)
{
  intrusive_node_t *current = list->head;
  while (current->next)
  {
    point_t *point = container_of(current->next, point_t, node);
    remove_node(list, current->next);
    free(point);
  }
}
