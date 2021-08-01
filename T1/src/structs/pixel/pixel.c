#include <stdio.h>
#include <stdlib.h>
#include "pixel.h"
#include "../imagelib/image.h"


Pixel* pixel_init(int location)
{
  Pixel* pixel = malloc(sizeof(Pixel));
  *pixel = (Pixel) {
    .location = location,
    .next = NULL,
  };
  // printf("Pixel initialized!\n");
  return pixel;
}

void pixel_destroy(Pixel* pixel)
{
  if (pixel -> next)
  {
    pixel_destroy(pixel -> next);
  }
  free(pixel);
}

void print_pixels(Pixel* pixel)
{
  printf("%i,", pixel -> location);
  Pixel* current = pixel -> next;
  while (current)
  {
    printf("%i,", current -> location);
    current = current -> next;
  }
  printf("\n");
}

void read_pixels(Pixel* pixel, Image* new_img, int umbral)
{
  new_img -> pixels[pixel -> location] = umbral;
  Pixel* current = pixel -> next;
  while (current)
  {
    new_img -> pixels[current -> location] = umbral;
    current = current -> next;
  }
}