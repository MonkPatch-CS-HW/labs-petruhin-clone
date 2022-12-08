#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include "bmp.h"

typedef enum process_cmd_status
{
  PROCESS_CMD_SUCCESS,
  PROCESS_CMD_INCORRECT_USAGE,
} process_cmd_status_t;

void process_crop_rotate(bmp_picture_t *bmp, char *infile, char *outfile, int x, int y, int w, int h)
{
  int res;

  if ((res = load_bmp(infile, bmp)) != 0)
  {
    printf("loading bmp failed... error code: %d\n", res);
    return;
  }

  if ((res = crop(bmp, x, y, w, h)) != 0)
  {
    printf("cropping bmp failed, error code: %d\n", res);
    return;
  }

  if ((res = rotate(bmp)) != 0)
  {
    printf("rotating bmp failed, error code: %d\n", res);
    return;
  }

  if ((res = save_bmp(outfile, bmp)) != 0)
  {
    printf("saving bmp failed, error code: %d\n", res);
    return;
  }
}

process_cmd_status_t process_cmd(int argc, char **argv, bmp_picture_t *bmp)
{
  if (argc < 2)
    return PROCESS_CMD_INCORRECT_USAGE;

  if (strcmp(argv[1], "crop-rotate") == 0)
  {
    if (argc < 8)
      return PROCESS_CMD_INCORRECT_USAGE;
    char *infile = argv[2];
    char *outfile = argv[3];
    int x = atoi(argv[4]);
    int y = atoi(argv[5]);
    int w = atoi(argv[6]);
    int h = atoi(argv[7]);
    process_crop_rotate(bmp, infile, outfile, x, y, w, h);
  }

  return PROCESS_CMD_SUCCESS;
}

int main(int argc, char **argv)
{
  bmp_picture_t *bmp = malloc(sizeof(bmp_picture_t));
  if (process_cmd(argc, argv, bmp) != 0)
    printf("incorrect usage\n");
  unload_bmp(bmp);
  free(bmp);
  return 0;
}