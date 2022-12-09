#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include "bmp.h"

/**
 * Return codes:
 * 0 on success,
 * -1 on any error
*/
int process_crop_rotate(bmp_picture_t *bmp, char *infile, char *outfile, int x, int y, int w, int h)
{
  int res = 0;

  if ((res = load_bmp(infile, bmp)) != 0)
  {
    printf("loading bmp failed... error code: %d\n", res);
    return -1;
  }

  if ((res = crop(bmp, x, y, w, h)) != 0)
  {
    printf("cropping bmp failed, error code: %d\n", res);
    return -1;
  }

  if ((res = rotate(bmp)) != 0)
  {
    printf("rotating bmp failed, error code: %d\n", res);
    return -1;
  }

  if ((res = save_bmp(outfile, bmp)) != 0)
  {
    printf("saving bmp failed, error code: %d\n", res);
    return -1;
  }

  return 0;
}

/**
 * Return codes:
 * 0 on success,
 * -1 on incorrect usage
 * -2 on command error
*/
int process_cmd(int argc, char **argv, bmp_picture_t *bmp)
{
  if (argc < 2)
    return -1;

  if (strcmp(argv[1], "crop-rotate") == 0)
  {
    if (argc < 8)
      return -1;
    char *infile = argv[2];
    char *outfile = argv[3];
    int x = atoi(argv[4]);
    int y = atoi(argv[5]);
    int w = atoi(argv[6]);
    int h = atoi(argv[7]);
    if (process_crop_rotate(bmp, infile, outfile, x, y, w, h) != 0)
      return -2;
  }

  return 0;
}

int main(int argc, char **argv)
{
  int res, ret = 0;
  bmp_picture_t *bmp = malloc(sizeof(bmp_picture_t));
  if ((res = process_cmd(argc, argv, bmp)) != 0)
  {
    if (res == -1)
      printf("incorrect usage\n");
    ret = 1;
  }
  unload_bmp(bmp);
  free(bmp);
  return ret;
}