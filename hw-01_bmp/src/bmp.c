#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"

int padd(int x)
{
  return (x + 3) - (x + 3) % 4;
}

load_bmp_status_t read_bmp(FILE *fp, bmp_picture_t *bmp)
{
  int res = 0;

  bmp->raw_data = NULL;
  bmp->pixel_data = NULL;

  if ((res = fread(&bmp->header, sizeof(bmp_header_t), 1, fp)) != 1)
    return LOAD_BMP_ERR_READ;
  if ((res = fread(&bmp->info, sizeof(bmp_info_v3_t), 1, fp)) != 1)
    return LOAD_BMP_ERR_READ;

  bmp->line_width = padd((bmp->info.bi_width * bmp->info.bi_bit_count) / 8);

  bmp->raw_data = malloc(bmp->info.bi_size_image);
  if (bmp->raw_data == NULL)
    return LOAD_BMP_ERR_ALLOC;

  if ((res = fseek(fp, bmp->header.bf_off_bits, SEEK_SET)) != 0)
    return LOAD_BMP_ERR_SEEK;
  if ((res = fread(bmp->raw_data, bmp->info.bi_size_image, 1, fp)) != 1)
    return LOAD_BMP_ERR_READ;

  bmp->pixel_data = malloc(bmp->info.bi_height * sizeof(pixel_data_t *));
  if (bmp->pixel_data == NULL)
    return LOAD_BMP_ERR_ALLOC;

  for (int i = 0; i < bmp->info.bi_height; i++)
    bmp->pixel_data[i] = (pixel_data_t *)((char *)bmp->raw_data + i * bmp->line_width);

  return LOAD_BMP_SUCCESS;
}

load_bmp_status_t write_bmp(FILE *fp, bmp_picture_t *bmp)
{
  int res = 0;

  if ((res = fwrite(&bmp->header, sizeof(bmp_header_t), 1, fp)) != 1)
    return SAVE_BMP_ERR_WRITE;
  if ((res = fwrite(&bmp->info, sizeof(bmp_info_v3_t), 1, fp)) != 1)
    return SAVE_BMP_ERR_WRITE;

  if ((res = fseek(fp, bmp->header.bf_off_bits, SEEK_SET)) != 0)
    return SAVE_BMP_ERR_SEEK;
  if ((res = fwrite(bmp->raw_data, bmp->info.bi_size_image, 1, fp)) != 1)
    return SAVE_BMP_ERR_WRITE;

  return SAVE_BMP_SUCCESS;
}

crop_status_t crop(bmp_picture_t *bmp, int x, int y, int w, int h)
{
  if (w <= 0 || h <= 0 || x < 0 || y < 0)
    return CROP_ERR_WRONG_ARG;

  if (x + w > bmp->info.bi_width || y + h > bmp->info.bi_height)
    return CROP_ERR_NO_FIT;

  bmp->info.bi_width = w;
  bmp->info.bi_height = h;
  bmp->line_width = padd((bmp->info.bi_width * bmp->info.bi_bit_count) / 8);
  bmp->info.bi_size_image = bmp->line_width * bmp->info.bi_height;

  pixel_data_t *raw_data = bmp->raw_data;
  pixel_data_t **pixel_data = bmp->pixel_data;

  bmp->raw_data = calloc(1, bmp->info.bi_size_image);
  if (bmp->raw_data == NULL)
    return CROP_ERR_ALLOC;
  bmp->pixel_data = malloc(bmp->info.bi_height * sizeof(pixel_data_t *));
  if (bmp->pixel_data == NULL)
    return CROP_ERR_ALLOC;

  for (int i = 0; i < bmp->info.bi_height; i++)
    bmp->pixel_data[i] = (pixel_data_t *)((char *)bmp->raw_data + i * bmp->line_width);

  for (int r = 0; r < bmp->info.bi_height; r++)
    for (int c = 0; c < bmp->info.bi_width; c++)
      bmp->pixel_data[r][c] = pixel_data[r + y][c + x];

  free(raw_data);
  free(pixel_data);

  return CROP_SUCCESS;
}

rotate_status_t rotate(bmp_picture_t *bmp)
{
  int tmp = bmp->info.bi_width;
  bmp->info.bi_width = bmp->info.bi_height;
  bmp->info.bi_height = tmp;
  bmp->line_width = padd((bmp->info.bi_width * bmp->info.bi_bit_count) / 8);
  bmp->info.bi_size_image = bmp->line_width * bmp->info.bi_height;

  pixel_data_t *raw_data = bmp->raw_data;
  pixel_data_t **pixel_data = bmp->pixel_data;

  bmp->raw_data = calloc(1, bmp->info.bi_size_image);
  if (bmp->raw_data == NULL)
    return ROTATE_ERR_ALLOC;
  bmp->pixel_data = malloc(bmp->info.bi_height * sizeof(pixel_data_t *));
  if (bmp->pixel_data == NULL)
    return ROTATE_ERR_ALLOC;

  for (int i = 0; i < bmp->info.bi_height; i++)
    bmp->pixel_data[i] = (pixel_data_t *)((char *)bmp->raw_data + i * bmp->line_width);

  for (int r = 0; r < bmp->info.bi_height; r++)
    for (int c = 0; c < bmp->info.bi_width; c++)
      bmp->pixel_data[r][c] = pixel_data[c][bmp->info.bi_height - 1 - r];

  free(raw_data);
  free(pixel_data);

  return ROTATE_SUCCESS;
}

load_bmp_status_t load_bmp(char *filepath, bmp_picture_t *bmp)
{
  FILE *fp = fopen(filepath, "r");
  if (fp == NULL)
    return LOAD_BMP_ERR_OPEN;

  int res = read_bmp(fp, bmp);
  fclose(fp);

  return res;
}

save_bmp_status_t save_bmp(char *filepath, bmp_picture_t *bmp)
{
  FILE *fp = fopen(filepath, "w");
  if (fp == NULL)
    return SAVE_BMP_ERR_OPEN;

  int res = write_bmp(fp, bmp);
  if (fclose(fp) != 0)
    return SAVE_BMP_ERR_CLOSE;

  return res;
}

void unload_bmp(bmp_picture_t *bmp)
{
  free(bmp->raw_data);
  free(bmp->pixel_data);
}