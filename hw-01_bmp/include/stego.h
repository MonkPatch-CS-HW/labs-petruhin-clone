#ifndef STEGO_H
#define STEGO_H

#include "bmp.h"

int insert(bmp_picture_t *bmp, char *keyfile, char *msgfile);
int extract(bmp_picture_t *bmp, char *keyfile, char *msgfile);

#endif // STEGO_H