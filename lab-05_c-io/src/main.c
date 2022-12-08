#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "clist.h"
#include "pose_list.h"

/*=== READ OPERATIONS ===*/

void load_txt(FILE *fd, intrusive_list_t *dst) {
  int x, y;
  while (fscanf(fd, "%d %d", &x, &y) == 2) {
    add_position(dst, x, y);
  }
}

int expand_left(int val) {
  static const size_t VAL_BYTES = 3;
  int mask = val & (1 << (8*VAL_BYTES - 1)) ? 0xFF : 0x00;
  size_t i = VAL_BYTES;
  while (i < sizeof(int)) {
    size_t offset = 8*i++;
    val &= ~(0xFF << offset);
    val |= mask << offset;
  }
  return val;
}

void load_bin(FILE *fd, intrusive_list_t *dst) {
  int buff_x, buff_y;
  while (fread(&buff_x, 3, 1, fd) == 1 &&
         fread(&buff_y, 3, 1, fd) == 1) {
    buff_x = expand_left(buff_x);
    buff_y = expand_left(buff_y);
    add_position(dst, buff_x, buff_y);
  }
}

/*=== ACTIONS ===*/

// write txt

void save_txt_op(intrusive_node_t *n, void *data) {
  position_node_t *pose = container_of(n, position_node_t, node);
  fprintf((FILE *)data, "%d %d\n", pose->x, pose->y);
}

void save_txt(FILE *fd, char *fmt, intrusive_list_t *src) {
  apply(src, save_txt_op, fd);
}

// write bin

void save_bin_op(intrusive_node_t *n, void *data) {
  position_node_t *pose = container_of(n, position_node_t, node);
  FILE *fd = (FILE *)data;
  assert(fwrite(&pose->x, 3, 1, fd) == 1);
  assert(fwrite(&pose->y, 3, 1, fd) == 1);
}

void save_bin(FILE *fd, char *fmt, intrusive_list_t *src) {
  apply(src, save_bin_op, fd);
}

// count

void count_op(intrusive_node_t *n, void *data) {
  (*(int *)data)++;
}

void print_count(FILE *fd, char *fmt, intrusive_list_t *src) {
  int cnt = 0;
  apply(src, count_op, &cnt);
  fprintf(fd, "%d\n", cnt);
}

// print

void print_op(intrusive_node_t *n, void *data) {
  position_node_t *pose = container_of(n, position_node_t, node);
  fprintf(stdout, (char *)data, pose->x, pose->y);
}

void print_poses(FILE *fd, char *fmt, intrusive_list_t *src) {
  apply(src, print_op, fmt);
  fprintf(stdout, "\n");
}

/*=== Operations Context ===*/

struct OpCtx {
  intrusive_list_t poses;

  FILE *in_file;
  void (*read_op)(FILE *fd, intrusive_list_t *il);

  FILE *out_file;
  void (*write_op)(FILE *fd, char *fmt, intrusive_list_t *il);
  void *arg;
};

void init_file_numbers(struct OpCtx *ctx, int argc, char **argv) {
  char *in_file_fmt = argv[1],
       *file_name = argv[2],
       *file_action = argv[3];

  ctx->in_file = fopen(file_name, "r");
  assert(ctx->in_file);
  if (!strcmp(in_file_fmt, "loadtext")) {
    ctx->read_op = load_txt;
  } else if (!strcmp(in_file_fmt, "loadbin")) {
    ctx->read_op = load_bin;
  } else {
    fprintf(stderr, "Error: unknown in file fmt %s\n", in_file_fmt);
    exit(-1);
  }

  if (!strcmp(file_action, "savetext") ||
      !strcmp(file_action, "savebin")) {
    ctx->out_file = fopen(argv[4], "w");
    ctx->write_op = !strcmp(file_action, "savetext") ? save_txt : save_bin;
  } else if (!strcmp(file_action, "print")) {
    ctx->out_file = stdout;
    ctx->arg = argv[4];
    ctx->write_op = print_poses;
  } else if (!strcmp(file_action, "count")) {
    ctx->out_file = stdout;
    ctx->write_op = print_count;
  } else {
    fprintf(stderr, "Error: unknown action %s\n", file_action);
    exit(-1);
  }

  init_list(&ctx->poses);
}

void cleanup_file_numbers(struct OpCtx *ctx) {
  if (ctx->in_file != stdin) {
    fclose(ctx->in_file);
  }
  if (ctx->out_file != stdout) {
    fclose(ctx->out_file);
  }

  remove_all_positions(&ctx->poses);
}

int main(int argc, char **argv) {
  struct OpCtx ctx;
  init_file_numbers(&ctx, argc, argv);

  ctx.read_op(ctx.in_file, &ctx.poses);
  ctx.write_op(ctx.out_file, ctx.arg, &ctx.poses);

  cleanup_file_numbers(&ctx);
  return 0;
}
