#pragma once
#include "../imagelib/image.h"

typedef struct pixel
{
  int location;
  struct pixel* next;
} Pixel;

Pixel* pixel_init(int location);
void pixel_destroy(Pixel* pixel);
void print_pixels(Pixel* pixel);
void read_pixels(Pixel* pixel, Image* new_img, int umbral);