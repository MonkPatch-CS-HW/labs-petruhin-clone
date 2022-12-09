#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include "bmp.h"
#include "stego.h"

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

int process_insert(bmp_picture_t *bmp, char *infile, char *outfile, char *keyfile, char *msgfile)
{
  int res;

  if ((res = load_bmp(infile, bmp)) != 0)
  {
    printf("loading bmp failed, error code: %d\n", res);
    return -1;
  }

  if ((res = insert(bmp, keyfile, msgfile)) != 0)
  {
    printf("inserting text failed, error code: %d\n", res);
    return -1;
  }

  if ((res = save_bmp(outfile, bmp)) != 0)
  {
    printf("saving bmp failed, error code: %d\n", res);
    return -1;
  }

  return 0;
}

int process_extract(bmp_picture_t *bmp, char *infile, char *keyfile, char *msgfile)
{
  int res;

  if ((res = load_bmp(infile, bmp)) != 0)
  {
    printf("loading bmp failed... error code: %d\n", res);
    return -1;
  }

  if ((res = extract(bmp, keyfile, msgfile)) != 0)
  {
    printf("extracting text failed, error code: %d\n", res);
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
    if (process_crop_rotate(bmp, argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7])) != 0)
      return -2;
  }
  else if (strcmp(argv[1], "insert") == 0)
  {
    if (argc < 6)
      return -1;
    if (process_insert(bmp, argv[2], argv[3], argv[4], argv[5]) != 0)
      return -2;
  }
  else if (strcmp(argv[1], "extract") == 0)
  {
    if (argc < 5)
      return -1;
    if (process_extract(bmp, argv[2], argv[3], argv[4]) != 0)
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