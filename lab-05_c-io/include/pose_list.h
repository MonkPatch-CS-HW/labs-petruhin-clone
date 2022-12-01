#ifndef POSE_LIST_H_INCLUDED
#define POSE_LIST_H_INCLUDED

#include "clist.h"

struct position_node {
  int x, y;
  struct intrusive_node node;
};

typedef struct position_node position_node_t;

void show_all_positions(intrusive_list_t *il);
void add_position(intrusive_list_t *il, int x, int y);
void remove_position(intrusive_list_t *il, int x, int y);
void remove_all_positions(intrusive_list_t *il);

#endif
