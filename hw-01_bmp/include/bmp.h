#ifndef BMP_H
#define BMP_H

typedef struct bmp_header
{
  short bf_type;
  int bf_size;
  short bf_reserved1;
  short bf_reserved2;
  int bf_off_bits;
} __attribute__((packed)) bmp_header_t;

typedef struct bmp_info_v3
{
  int bi_size;
  int bi_width;
  int bi_height;
  short bi_planes;
  short bi_bit_count;
  int bi_compression;
  int bi_size_image;
  int bi_xPels_per_meter;
  int bi_yPels_per_meter;
  int bi_clr_used;
  int bi_clr_important;
} __attribute__((packed)) bmp_info_v3_t;

typedef struct pixel_data
{
  unsigned char b;
  unsigned char g;
  unsigned char r;
} __attribute__((packed)) pixel_data_t;


typedef struct bmp_picture
{
  bmp_header_t header;
  bmp_info_v3_t info;
  pixel_data_t *raw_data;
  pixel_data_t **pixel_data;
  int line_width;
  int lines_count;
} bmp_picture_t;

typedef enum load_bmp_status
{
  LOAD_BMP_SUCCESS,
  LOAD_BMP_ERR_OPEN,
  LOAD_BMP_ERR_READ,
  LOAD_BMP_ERR_ALLOC,
  LOAD_BMP_ERR_SEEK,
} load_bmp_status_t;

typedef enum save_bmp_status
{
  SAVE_BMP_SUCCESS,
  SAVE_BMP_ERR_OPEN,
  SAVE_BMP_ERR_WRITE,
  SAVE_BMP_ERR_SEEK,
  SAVE_BMP_ERR_CLOSE,
} save_bmp_status_t;

typedef enum crop_status
{
  CROP_SUCCESS,
  CROP_ERR_WRONG_ARG,
  CROP_ERR_NO_FIT,
  CROP_ERR_ALLOC,
} crop_status_t;

typedef enum rotate_status
{
  ROTATE_SUCCESS,
  ROTATE_ERR_ALLOC,
} rotate_status_t;

int padd(int x);
load_bmp_status_t load_bmp(char *filepath, bmp_picture_t *bmp);
crop_status_t crop(bmp_picture_t *bmp, int x, int y, int w, int h);
rotate_status_t rotate(bmp_picture_t *bmp);
save_bmp_status_t save_bmp(char *filepath, bmp_picture_t *bmp);
void unload_bmp(bmp_picture_t *bmp);

#endif // BMP_H