#include <stdio.h>
#include <stdlib.h>
#include "neighborhood.h"
#include "../pixel/pixel.h"
#include "../imagelib/image.h"


Neighborhood* neighborhood_init()
{
  Neighborhood* neighborhood = malloc(sizeof(Neighborhood));
  *neighborhood = (Neighborhood) {
    .min_umbral = 128,
    .area = 0,
    .pixels = NULL,
  };
  return neighborhood;
}

void get_neighborhood(int umbral, Image* image, int location, Neighborhood* neighborhood, int* visited)
{
  Pixel* current = pixel_init(location);
  Pixel* head = current;
  Pixel* tail = current;

  while (current)
  {
    if (current -> location >=0 && ! visited[current -> location] && image -> pixels[current -> location] >= umbral)
    {
      add_neighbor(image, neighborhood, visited, current -> location);
    }

    int* neighbors = get_4_neighbors(umbral, image, current -> location);
    for (int i = 0; i < 4; i++)
    {
      int neighbor_location = neighbors[i];
      if (neighbor_location >=0 && ! visited[neighbor_location] && image -> pixels[neighbor_location] >= umbral)
      {
        add_neighbor(image, neighborhood, visited, neighbor_location);
        Pixel* pixel = pixel_init(neighbor_location);
        tail -> next = pixel;
        tail = tail -> next;
      }
    }
    free(neighbors);
    current = current -> next;
  }
  pixel_destroy(head);
}

void add_neighbor(Image* image, Neighborhood* neighborhood, int* visited, int neighbor_location)
{
  Pixel* pixel = pixel_init(neighbor_location);
  if (neighborhood -> pixels)
  {
    pixel -> next = neighborhood -> pixels;
    neighborhood -> pixels = pixel;
  }
  else
  {
    neighborhood -> pixels = pixel;
  }
  if (image -> pixels[neighbor_location] < neighborhood -> min_umbral)
  {
    neighborhood -> min_umbral = image -> pixels[neighbor_location];
  }
  neighborhood -> area ++;
  visited[neighbor_location] = 1;
}

int* get_4_neighbors(int umbral, Image* image, int location)
{
  int j = location % image -> width;
  int i = location / image -> width;
  int * neighbors = calloc(4, sizeof(int));
  get_neighbor(umbral, image, i - 1, j    , neighbors, 0);
  get_neighbor(umbral, image, i    , j + 1, neighbors, 1);
  get_neighbor(umbral, image, i + 1, j    , neighbors, 2);
  get_neighbor(umbral, image, i    , j - 1, neighbors, 3);
  return neighbors;
}

void get_neighbor(int umbral, Image* image, int i, int j, int* neighbors, int position)
{
  if (0 <= j && j < image -> width && 0 <= i && i < image -> height)
  {
    int new_location = i * (image -> width) + j;
    if (image -> pixels[new_location] >= umbral)
    {neighbors[position] = new_location;}
    else
    {neighbors[position] = -1;}    
  }
  else
  {neighbors[position] = -1;}
}
