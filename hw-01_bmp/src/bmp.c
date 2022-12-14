#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bmp.h"

int padd(int x)
{
  return (x + 3) - (x + 3) % 4;
}

/**
 * Return codes:
 * 0 on success,
 * -1 on allocation error,
 */
int make_of_size(bmp_picture_t *bmp, int width, int height, bmp_picture_t *bkp)
{
  if (bkp != NULL)
    memcpy(bkp, bmp, sizeof(bmp_picture_t));

  bmp->raw_data = NULL;
  bmp->pixel_data = NULL;

  bmp->info.bi_width = width;
  bmp->info.bi_height = height;
  bmp->line_width = padd((bmp->info.bi_width * bmp->info.bi_bit_count) / 8);
  bmp->info.bi_size_image = bmp->line_width * height;
  bmp->header.bf_size = bmp->header.bf_off_bits + bmp->info.bi_size_image;

  bmp->raw_data = calloc(1, bmp->info.bi_size_image);
  if (bmp->raw_data == NULL)
    return -1;

  bmp->pixel_data = malloc(bmp->info.bi_height * sizeof(pixel_data_t *));
  if (bmp->pixel_data == NULL)
    return -1;

  for (int i = 0; i < bmp->info.bi_height; i++)
    bmp->pixel_data[bmp->info.bi_height - i - 1] = (pixel_data_t *)(bmp->raw_data + i * bmp->line_width);

  return 0;
}

/**
 * Return codes:
 * 0 on success,
 * -2 on read error,
 * -3 on allocation error,
 * -4 on seek error
 */
int read_bmp(FILE *fp, bmp_picture_t *bmp)
{
  int res = 0;
  bmp->raw_data = NULL;
  bmp->pixel_data = NULL;

  if ((res = fread(&bmp->header, sizeof(bmp_header_t), 1, fp)) != 1)
    return -2;
  if ((res = fread(&bmp->info, sizeof(bmp_info_v3_t), 1, fp)) != 1)
    return -2;

  if (make_of_size(bmp, bmp->info.bi_width, bmp->info.bi_height, NULL) != 0)
    return -3;

  if ((res = fseek(fp, bmp->header.bf_off_bits, SEEK_SET)) != 0)
    return -4;
  if ((res = fread(bmp->raw_data, bmp->info.bi_size_image, 1, fp)) != 1)
    return -2;

  return 0;
}

/**
 * Return codes:
 * 0 on success,
 * -3 on write error,
 * -4 on seek error
 */
int write_bmp(FILE *fp, bmp_picture_t *bmp)
{
  int res = 0;

  if ((res = fwrite(&bmp->header, sizeof(bmp_header_t), 1, fp)) != 1)
    return -3;
  if ((res = fwrite(&bmp->info, sizeof(bmp_info_v3_t), 1, fp)) != 1)
    return -3;

  if ((res = fseek(fp, bmp->header.bf_off_bits, SEEK_SET)) != 0)
    return -4;
  if ((res = fwrite(bmp->raw_data, bmp->info.bi_size_image, 1, fp)) != 1)
    return -3;

  return 0;
}

/**
 * Return codes:
 * 0 on success,
 * -1 on incorrect parameters,
 * -2 on non-fitting rectangle,
 * -3 on allocation error
 */
int crop(bmp_picture_t *bmp, int x, int y, int w, int h)
{
  if (w <= 0 || h <= 0 || x < 0 || y < 0)
    return -1;

  if (x + w > bmp->info.bi_width || y + h > bmp->info.bi_height)
    return -2;

  bmp_picture_t bkp;
  if (make_of_size(bmp, w, h, &bkp) != 0)
    return -3;

  for (int r = 0; r < bmp->info.bi_height; r++)
    for (int c = 0; c < bmp->info.bi_width; c++)
      (bmp->pixel_data[r])[c] = bkp.pixel_data[r + y][c + x];

  unload_bmp(&bkp);
  return 0;
}

/**
 * Return codes:
 * 0 on success,
 * -1 on allocation error,
 */
int rotate(bmp_picture_t *bmp)
{

  bmp_picture_t bkp;
  if (make_of_size(bmp, bmp->info.bi_height, bmp->info.bi_width, &bkp) != 0)
    return -3;

  for (int r = 0; r < bmp->info.bi_height; r++)
    for (int c = 0; c < bmp->info.bi_width; c++)
      bmp->pixel_data[r][c] = bkp.pixel_data[bmp->info.bi_width - 1 - c][r];

  unload_bmp(&bkp);
  return 0;
}

/**
 * Return codes:
 * 0 on success,
 * -1 on open error,
 * -2 on read error,
 * -3 on allocation error,
 * -4 on seek error,
 */
int load_bmp(char *filepath, bmp_picture_t *bmp)
{
  FILE *fp = fopen(filepath, "r");
  if (fp == NULL)
    return -1;

  int res = read_bmp(fp, bmp);
  fclose(fp);

  return res;
}

/**
 * Return codes:
 * 0 on success,
 * -1 on open error,
 * -2 on close error,
 * -3 on write error,
 * -4 on seek error,
 */
int save_bmp(char *filepath, bmp_picture_t *bmp)
{
  FILE *fp = fopen(filepath, "w");
  if (fp == NULL)
    return -1;

  int res = write_bmp(fp, bmp);
  if (fclose(fp) != 0)
    return -2;

  return res;
}

void unload_bmp(bmp_picture_t *bmp)
{
  free(bmp->raw_data);
  free(bmp->pixel_data);
}
