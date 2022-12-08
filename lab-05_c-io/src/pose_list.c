#include "pose_list.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void remove_position(intrusive_list_t *il, int x, int y) {
  intrusive_node_t *node = il->head.next;
  while (node != &il->head) {
    position_node_t *pn = container_of(node, position_node_t, node);
    node = node->next;
    
    if (pn->x != x || pn->y != y) {
      continue;
    }
    remove_node(il, &pn->node);
    free(pn);
  }
}

void add_position(intrusive_list_t *il, int x, int y) {
  position_node_t *pn = malloc(sizeof(*pn));
  assert(pn);

  pn->x = x;
  pn->y = y;
  add_node(il, &pn->node);
}

void show_all_positions(intrusive_list_t *il) {
  intrusive_node_t *node = il->head.next;
  while (node != &il->head) {
    position_node_t *pn = container_of(node, position_node_t, node);
    printf("(%d %d) ", pn->x, pn->y);
    node = node->next;
  }
  printf("\n");
}

void remove_all_positions(intrusive_list_t *il) {
  while (il->head.next != &il->head) {
    intrusive_node_t *victim = il->head.next;
    remove_node(il, victim);
    free(container_of(victim, position_node_t, node));
  }
}
