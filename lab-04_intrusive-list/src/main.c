#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clist.h"

typedef struct point
{
  int x, y;
  intrusive_node_t node;
} point_t;

void add_point(intrusive_list_t *list, int x, int y)
{
  point_t *point = malloc(sizeof(point_t));
  point->x = x;
  point->y = y;

  add_node(list, &point->node);
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

int main()
{
  /* usage

     intrusive_list_t l;
     init_list(&l);

     add_point(&l, 10, 10);
     add_point(&l, 20, 20);

     show_all_points(&l);

     return 0;
  */
  intrusive_list_t l;
  init_list(&l);

  char cmd[8];
  while (1)
  {
    scanf("%8s", cmd);
    if (strcmp(cmd, "add") == 0)
    {
      int x, y;
      scanf("%d %d", &x, &y);
      add_point(&l, x, y);
    }
    else if (strcmp(cmd, "rm") == 0)
    {
      int x, y;
      scanf("%d %d", &x, &y);
      remove_point(&l, x, y);
    }
    else if (strcmp(cmd, "print") == 0)
      show_all_points(&l);
    else if (strcmp(cmd, "rma") == 0)
      remove_all_points(&l);
    else if (strcmp(cmd, "len") == 0)
      printf("%d\n", get_length(&l));
    else if (strcmp(cmd, "exit") == 0)
    {
      remove_all_points(&l);
      break;
    }
    else
      printf("Unknown command\n");
  }
  uninit_list(&l);
  return 0;
}
