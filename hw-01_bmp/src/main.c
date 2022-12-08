#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>

typedef struct bmp_header
{
  short bfType;
  int bfSize;
  short bfReserved1;
  short bfReserved2;
  int bfOffBits;
} __attribute__((packed)) bmp_header_t;

typedef struct bmp_info_v3
{
  int biSize;
  int biWidth;
  int biHeight;
  short biPlanes;
  short biBitCount;
  int biCompression;
  int biSizeImage;
  int biXPelsPerMeter;
  int biYPelsPerMeter;
  int biClrUsed;
  int biClrImportant;
} __attribute__((packed)) bmp_info_v3_t;

typedef struct pixel_data
{
  unsigned char b;
  unsigned char g;
  unsigned char r;
} __attribute__((packed)) pixel_data_t;

void print_pixel(pixel_data_t pd)
{
  printf("(%d, %d, %d) ", pd.r, pd.g, pd.b);
}

int main()
{
  FILE *fp = fopen("pns.bmp", "r");
  bmp_header_t *header = malloc(sizeof(bmp_header_t));
  fread(header, sizeof(bmp_header_t), 1, fp);
  printf("BMP HEADER\n");
  printf("(offset=%lu) bfType: %d\n", offsetof(bmp_header_t, bfType), header->bfType);
  printf("(offset=%lu) bfSize: %d\n", offsetof(bmp_header_t, bfSize), header->bfSize);
  printf("(offset=%lu) bfReserved1: %d\n", offsetof(bmp_header_t, bfReserved1), header->bfReserved1);
  printf("(offset=%lu) bfReserved2: %d\n", offsetof(bmp_header_t, bfReserved2), header->bfReserved2);
  printf("(offset=%lu) bfOffBits: %d\n", offsetof(bmp_header_t, bfOffBits), header->bfOffBits);
  printf("\n");
  // fseek(fp, header->bfOffBits, SEEK_SET);
  bmp_info_v3_t *info = malloc(sizeof(bmp_info_v3_t));
  fread(info, sizeof(bmp_info_v3_t), 1, fp);
  printf("BMP INFO\n");
  printf("(offset=%lu) biSize: %d\n", offsetof(bmp_info_v3_t, biSize), info->biSize);
  printf("(offset=%lu) biWidth: %d\n", offsetof(bmp_info_v3_t, biWidth), info->biWidth);
  printf("(offset=%lu) biHeight: %d\n", offsetof(bmp_info_v3_t, biHeight), info->biHeight);
  printf("(offset=%lu) biPlanes: %d\n", offsetof(bmp_info_v3_t, biPlanes), info->biPlanes);
  printf("(offset=%lu) biBitCount: %d\n", offsetof(bmp_info_v3_t, biBitCount), info->biBitCount);
  printf("(offset=%lu) biCompression: %d\n", offsetof(bmp_info_v3_t, biCompression), info->biCompression);
  printf("(offset=%lu) biSizeImage: %d\n", offsetof(bmp_info_v3_t, biSizeImage), info->biSizeImage);
  printf("(offset=%lu) biXPelsPerMeter: %d\n", offsetof(bmp_info_v3_t, biXPelsPerMeter), info->biXPelsPerMeter);
  printf("(offset=%lu) biYPelsPerMeter: %d\n", offsetof(bmp_info_v3_t, biYPelsPerMeter), info->biYPelsPerMeter);
  printf("(offset=%lu) biClrUsed: %d\n", offsetof(bmp_info_v3_t, biClrUsed), info->biClrUsed);
  printf("(offset=%lu) biClrImportant: %d\n", offsetof(bmp_info_v3_t, biClrImportant), info->biClrImportant);
  // pixel_data_t* raw_data = malloc(pixel_data)
  fseek(fp, header->bfOffBits, SEEK_SET);
  pixel_data_t *raw_data = malloc(info->biSizeImage);
  fread(raw_data, info->biSizeImage, 1, fp);
  pixel_data_t **image_data = malloc(info->biHeight * sizeof(pixel_data_t *));
  int widthDiv4 = (info->biWidth * 3 + 3) - (info->biWidth * 3 + 3) % 4;
  for (int i = 0; i < info->biHeight; i++)
  {
    int byteOffset = i * widthDiv4;
    image_data[i] = (pixel_data_t *)((char *)raw_data + byteOffset);
  }
  // printf("image_data[0][0] = r:%d, g:%d, b:%d\n", image_data[0][0].r, image_data[0][0].g, image_data[0][0].b);
  fclose(fp);

  bmp_header_t *new_header = malloc(sizeof(bmp_header_t));
  bmp_info_v3_t *new_info = malloc(sizeof(bmp_info_v3_t));
  memcpy(new_header, header, sizeof(bmp_header_t));
  memcpy(new_info, info, sizeof(bmp_info_v3_t));
  new_info->biWidth = info->biHeight;
  new_info->biHeight = info->biWidth;
  int newWidthDiv4 = (new_info->biWidth * 3 + 3) - (new_info->biWidth * 3 + 3) % 4;
  new_info->biSizeImage = newWidthDiv4 * new_info->biHeight;
  pixel_data_t *new_raw_data = calloc(new_info->biSizeImage, 1);

  pixel_data_t **new_image_data = malloc(new_info->biHeight * sizeof(pixel_data_t *));
  for (int i = 0; i < new_info->biHeight; i++)
  {
    int byteOffset = i * newWidthDiv4;
    new_image_data[i] = (pixel_data_t *)((char *)new_raw_data + byteOffset);
    // printf("row %d, offset %d\n", i, byteOffset);
  }

  // for (int r = 0; r < info->biHeight; r++)
  // {
  //   for (int c = 0; c < info->biWidth; c++)
  //   {
  //     print_pixel(image_data[r][c]);
  //   }
  // }
  for (int r = 0; r < new_info->biHeight; r++)
  {
    for (int c = 0; c < new_info->biWidth; c++)
    {
      // printf("{c=%d, r=%d}: ", c, r);
      new_image_data[r][c] = image_data[new_info->biWidth - 1 - c][r];
      // printf("pixel[%d, %d]=", r, c);
      // print_pixel(image_data[c][r]);
      // printf("\n");
    }
  }
  // for (int i = 0; i < new_info->biSizeImage; i++)
  // {
  //   printf("%d ", ((char*)new_raw_data)[i]);
  // }
  printf("\n");
  FILE *ofp = fopen("output.bmp", "w");
  fwrite(new_header, sizeof(bmp_header_t), 1, ofp);
  fwrite(new_info, sizeof(bmp_info_v3_t), 1, ofp);
  fseek(ofp, new_header->bfOffBits, SEEK_SET);
  fwrite(new_raw_data, new_info->biSizeImage, 1, ofp);
  fclose(ofp);
  return 0;
}