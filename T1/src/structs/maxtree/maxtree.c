#include <stdio.h>
#include <stdlib.h>
#include "maxtree.h"
#include "../pixel/pixel.h"
#include "../imagelib/image.h"
#include "../neighborhood/neighborhood.h"


Maxtree* maxtree_init(int umbral, int area)
{
  Maxtree* maxtree = malloc(sizeof(Maxtree));
  *maxtree = (Maxtree) {
    .umbral = umbral,
    .area = area,
    .pixels = NULL,
    .parent = NULL,
    .head = NULL,
    .next = NULL,
  };
  // printf("Maxtree initialized!\n");
  return maxtree;
}

Maxtree* add_child(Maxtree* maxtree, int umbral, int area)
{
  Maxtree* child = maxtree_init(umbral, area);
  child -> parent = maxtree;
  if (! maxtree -> head)
  {
    maxtree -> head = child;
  }
  else
  {
    Maxtree* tail = maxtree -> head;
    while (tail -> next)
    {
      tail = tail -> next;
    }
    tail -> next = child;
  }
  return child;
}

void add_pixel(Maxtree* maxtree, int location)
{
  Pixel* pixel = pixel_init(location);
  if (maxtree -> pixels)
  {
    pixel -> next = maxtree -> pixels;
    maxtree -> pixels = pixel;
  }
  else
  {
    maxtree -> pixels = pixel;
  }
}

void maxtree_destroy(Maxtree* maxtree)
{
  Maxtree* current = maxtree -> head;
  while (current)
  {
    Maxtree* next = current -> next;
    maxtree_destroy(current);
    current = next;
  }
  pixel_destroy(maxtree -> pixels);
  free(maxtree);
}

void print_nodes(Maxtree* maxtree)
{
  printf("My umbral: %i\n", maxtree -> umbral);
  printf("My area: %i\n", maxtree -> area);
  if (maxtree -> parent)
  {
    printf("Parent umbral: %i\n", maxtree -> parent -> umbral);
  }
  printf("Pixels: ");
  print_pixels(maxtree -> pixels);
  Maxtree* current = maxtree -> head;
  while (current)
  {
    print_nodes(current); // Esto se cambio
    current = current -> next;
  }
}


void generate_tree(Maxtree* maxtree, Image* image, Neighborhood* neighborhood, int* visited, int* neigh_visited)
{
  Pixel* pixels = neighborhood -> pixels;
  while (pixels)
  {
    if (image -> pixels[pixels -> location] == neighborhood -> min_umbral)
    {
      visited[pixels -> location] = 1;
      add_pixel(maxtree, pixels -> location);
    }
    pixels = pixels -> next;
  }

  pixels = neighborhood -> pixels;
  while (pixels)
  {
    if (! visited[pixels -> location])
    {
      Neighborhood* new_neighborhood = neighborhood_init();
      get_neighborhood(neighborhood -> min_umbral + 1, image, pixels -> location, new_neighborhood, neigh_visited);
      Pixel* pixel = new_neighborhood -> pixels;
      while (pixel)
      {
        neigh_visited[pixel -> location] = 0;
        pixel = pixel -> next;
      }
      
      Maxtree* child_maxtree = add_child(maxtree, new_neighborhood -> min_umbral, new_neighborhood -> area);
      generate_tree(child_maxtree, image, new_neighborhood, visited, neigh_visited);
      pixel_destroy(new_neighborhood -> pixels);
      
      free(new_neighborhood);
    }
    pixels = pixels -> next;
  }
}

void read_tree(Maxtree* maxtree, Image* new_img)
{
  Maxtree* current = maxtree -> head;
  while (current)
  {
    read_tree(current, new_img);
    current = current -> next;
  }
  read_pixels(maxtree -> pixels, new_img, maxtree -> umbral);
}

void area_filter(Maxtree* maxtree, int min_area, int threshold)
{
  if (maxtree -> umbral <= threshold || maxtree -> area <= min_area)
  {
    if (maxtree -> parent)
    {
      maxtree -> umbral = maxtree -> parent -> umbral;
    }
    else
    {
      maxtree -> umbral = 0;
    }
  }
  Maxtree* current = maxtree -> head;
  while (current)
  {
    area_filter(current, min_area, threshold);
    current = current -> next;
  }
}

void delta_filter(Maxtree* maxtree, float max_delta)
{
  if (maxtree -> parent)
  {
    float new_delta = (float)(maxtree -> parent -> area - maxtree -> area) / (maxtree -> parent -> area);
    if (new_delta >= max_delta)
    {
      maxtree -> umbral = maxtree -> parent -> umbral;
    }
  }
  else
  {
    maxtree -> umbral = 0;
  }
  Maxtree* current = maxtree -> head;
  while (current)
  {
    delta_filter(current, max_delta);
    current = current -> next;
  }
}