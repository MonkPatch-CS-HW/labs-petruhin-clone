#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"
#include "stego.h"

unsigned char *get_byte_ptr(bmp_picture_t *bmp, int x, int y, char chan)
{
  if (x < 0 || y < 0 || x >= bmp->info.bi_width || y >= bmp->info.bi_height)
    return NULL;

  switch (chan)
  {
  case 'R':
  case 'r':
    return &bmp->pixel_data[y][x].r;
  case 'G':
  case 'g':
    return &bmp->pixel_data[y][x].g;
  case 'B':
  case 'b':
    return &bmp->pixel_data[y][x].b;
  default:
    return NULL;
  }
}

int set_bit(bmp_picture_t *bmp, char bit, int x, int y, char chan)
{
  unsigned char *byte = get_byte_ptr(bmp, x, y, chan);
  if (byte == NULL)
    return 1;
  *byte = (*byte & ~1) | (bit & 1);
  return 0;
}

int get_bit(bmp_picture_t *bmp, int x, int y, char chan)
{
  unsigned char *byte = get_byte_ptr(bmp, x, y, chan);
  if (byte == NULL)
    return 0;
  return *byte & 1;
}

int char_to_code(char c)
{
  switch (c)
  {
  case '\0':
    return 0;
  case ' ':
    return 1;
  case '.':
    return 2;
  case ',':
    return 3;
  default:
    if ('A' <= c && c <= 'Z')
      return 4 + c - 'A';
    return 31;
  }
}

char code_to_char(int c)
{
  switch (c)
  {
  case 0:
    return '\0';
  case 1:
    return ' ';
  case 2:
    return '.';
  case 3:
    return ',';
  default:
    if (4 <= c && c <= 4 + 'Z' - 'A')
      return c - 4 + 'A';
    return '?';
  }
}

int insert_char(bmp_picture_t *bmp, FILE *fp, char c)
{
  int code = char_to_code(c);
  int res, x, y;
  char chan;
  for (int i = 0; i < 5; i++)
  {
    if ((res = fscanf(fp, "%d %d %c", &x, &y, &chan)) != 3)
      return 1;
    set_bit(bmp, code & 1, x, y, chan);
    code >>= 1;
  }
  return 0;
}

/**
 * Return codes:
 * 0 on success,
 * -1 on key chunk read error
*/
int extract_char(bmp_picture_t *bmp, FILE *fp, char *c)
{
  int code = 0;
  int res, x, y;
  char chan;
  int base = 0;
  for (int i = 0; i < 5; i++)
  {
    if ((res = fscanf(fp, "%d %d %c", &x, &y, &chan)) != 3)
      return -1;
    code |= get_bit(bmp, x, y, chan) << base++;
  }
  *c = code_to_char(code);
  return 0;
}

/**
 * Return codes:
 * 0 on success,
 * -5 on inserting error
 */
int _insert_fp(bmp_picture_t *bmp, FILE *kfp, FILE *mfp)
{
  int res;
  char c;
  while ((res = fread(&c, sizeof(char), 1, mfp)) == 1)
    if (insert_char(bmp, kfp, c) != 0)
    {
      return -5;
      break;
    }
  insert_char(bmp, kfp, '\0');
  return 0;
}

/**
 * Return codes:
 * 0 on success
 */
int _extract_fp(bmp_picture_t *bmp, FILE *kfp, FILE *mfp)
{
  int res;
  char c = 1;
  while (1)
  {
    if ((res = extract_char(bmp, kfp, &c)) != 0)
      break;
    if (c == 0)
      break;
    fwrite(&c, sizeof(char), 1, mfp);
  }
  return 0;
}

/**
 * Return codes:
 * 0 on success,
 * -3 on key file open error
 * -4 on message file open error
 */
int close_files(FILE *kfp, FILE *mfp)
{
  int res = 0;
  if (kfp != NULL && fclose(kfp) != 0)
    res = -3;
  if (mfp != NULL && fclose(mfp) != 0)
    res = -4;
  return res;
}

/**
 * Return codes:
 * 0 on success,
 * -1 on key file open error
 * -2 on message file open error
 */
int open_files(FILE **kfp, FILE **mfp, char *mfp_mode, char *keyfile, char *msgfile)
{
  int res = 0;
  *kfp = fopen(keyfile, "r");
  if (*kfp == NULL)
    res = -1;
  *mfp = fopen(msgfile, mfp_mode);
  if (*mfp == NULL)
    res = -2;
  if (res != 0)
    close_files(*kfp, *mfp);
  return res;
}

/**
 * Return codes:
 * 0 on success
 * -1 on key file open error,
 * -2 on message file open error,
 * -3 on key file close error,
 * -4 on message file close error,
 * -5 on inserting error
 */
int insert(bmp_picture_t *bmp, char *keyfile, char *msgfile)
{
  int res;
  FILE *kfp = NULL;
  FILE *mfp = NULL;

  if ((res = open_files(&kfp, &mfp, "r", keyfile, msgfile)) != 0)
    return res;

  if ((res = _insert_fp(bmp, kfp, mfp)) != 0)
    return res;

  if ((res = close_files(kfp, mfp)) != 0)
    return res;

  return 0;
}

/**
 * Return codes:
 * 0 on success
 * -1 on key file open error,
 * -2 on message file open error,
 * -3 on key file close error,
 * -4 on message file close error,
 * -5 on extracting error
 */
int extract(bmp_picture_t *bmp, char *keyfile, char *msgfile)
{
  int res;
  FILE *kfp = NULL;
  FILE *mfp = NULL;

  if ((res = open_files(&kfp, &mfp, "w", keyfile, msgfile)) != 0)
    return res;

  if ((res = _extract_fp(bmp, kfp, mfp)) != 0)
    return res;

  if ((res = close_files(kfp, mfp)) != 0)
    return res;

  return 0;
}