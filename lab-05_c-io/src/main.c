#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clist.h"
#include "point_list.h"

#define UNUSED(x) (void)(x)
#define BIT_24 0x800000
#define BITS_24 0xffffff
#define BITS_HIGHER_THAN_24 ~BITS_24

int from_int24(int x)
{
  if (x & BIT_24)
    return x | BITS_HIGHER_THAN_24;
  return x & BITS_24;
}

int to_int24(int x)
{
  return x & BITS_24;
}

typedef struct callback_param
{
  FILE *file;
  intrusive_list_t *list;
} callback_param_t;

void read_text_point_callback(intrusive_node_t *node, void *data)
{
  UNUSED(node);
  callback_param_t *param = (callback_param_t *)data;
  int x, y;
  int res = fscanf(param->file, "%d %d\n", &x, &y);
  if (res < 2)
    return;
  add_point_back(param->list, x, y);
}

void read_binary_point_callback(intrusive_node_t *node, void *data)
{
  UNUSED(node);
  callback_param_t *param = (callback_param_t *)data;
  int x = 0, y = 0;
  int res1 = fread(&x, sizeof(char), 3, param->file);
  int res2 = fread(&y, sizeof(char), 3, param->file);
  if (res1 < 3 || res2 < 3)
    return;
  x = from_int24(x);
  y = from_int24(y);
  add_point_back(param->list, x, y);
}

void write_text_point_callback(intrusive_node_t *node, void *data)
{
  callback_param_t *param = (callback_param_t *)data;
  point_t *point = container_of(node, point_t, node);
  fprintf(param->file, "%d %d\n", point->x, point->y);
}

void write_binary_point_callback(intrusive_node_t *node, void *data)
{
  callback_param_t *param = (callback_param_t *)data;
  point_t *point = container_of(node, point_t, node);
  int x = to_int24(point->x);
  int y = to_int24(point->y);
  fwrite(&x, sizeof(char), 3, param->file);
  fwrite(&y, sizeof(char), 3, param->file);
}

void print_callback(intrusive_node_t *node, void *data)
{
  point_t *point = container_of(node, point_t, node);
  printf((char *)data, point->x, point->y);
}

void count_callback(intrusive_node_t *node, void *data)
{
  UNUSED(node);
  (*(int *)data)++;
}

int process_file_load(char *operation, char *infile, intrusive_list_t *list)
{
  void (*callback)(intrusive_node_t * node, void *data);
  if (strcmp(operation, "loadtext") == 0)
    callback = read_text_point_callback;
  else if (strcmp(operation, "loadbin") == 0)
    callback = read_binary_point_callback;
  else
    return -1;
  FILE *file = fopen(infile, "r");
  if (file == NULL)
    return -2;
  callback_param_t c = {.file = file, .list = list};
  // temporary point for apply() to work
  add_point(list, __INT_MAX__, __INT_MAX__);
  apply(list, callback, &c);
  remove_point(list, __INT_MAX__, __INT_MAX__);
  fclose(file);
  return 0;
}

int process_action(char *action, char **args, intrusive_list_t *list)
{
  if (strcmp(action, "count") == 0)
  {
    int counter = 0;
    apply(list, count_callback, &counter);
    printf("%d\n", counter);
    return 0;
  }

  if (strcmp(action, "print") == 0)
  {
    apply(list, print_callback, args[0]);
    printf("\n");
    return 0;
  }

  void (*callback)(intrusive_node_t * node, void *data);
  if (strcmp(action, "savetext") == 0)
    callback = write_text_point_callback;
  else if (strcmp(action, "savebin") == 0)
    callback = write_binary_point_callback;
  else
    return -1;

  FILE *file = fopen(args[0], "w");
  if (file == NULL)
    return -2;
  callback_param_t c = {.file = file, .list = list};
  apply(list, callback, &c);
  fclose(file);
  return 0;
}

int run(int argc, char **argv, intrusive_list_t *list)
{
  if (argc < 4)
  {
    printf("incorrect usage\n");
    return 1;
  }
  if (process_file_load(argv[1], argv[2], list) < 0)
  {
    printf("error while opening/reading the file");
    return 2;
  }
  if (process_action(argv[3], argv + 4, list) < 0)
  {
    printf("could not execute action\n");
    return 3;
  }
  return 0;
}

int main(int argc, char **argv)
{
  intrusive_list_t l;
  init_list(&l);
  int res = run(argc, argv, &l);
  remove_all_points(&l);
  uninit_list(&l);
  return res;
}
