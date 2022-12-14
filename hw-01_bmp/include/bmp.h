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
  char *raw_data;
  pixel_data_t **pixel_data;
  int line_width;
} bmp_picture_t;

int padd(int x);
int load_bmp(char *filepath, bmp_picture_t *bmp);
int crop(bmp_picture_t *bmp, int x, int y, int w, int h);
int rotate(bmp_picture_t *bmp);
int save_bmp(char *filepath, bmp_picture_t *bmp);
void unload_bmp(bmp_picture_t *bmp);

#endif // BMP_H