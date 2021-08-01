#pragma once
#include "../pixel/pixel.h"
#include "../imagelib/image.h"

typedef struct neighborhood
{
  int min_umbral;
  int area;
  Pixel* pixels;
} Neighborhood;

Neighborhood* neighborhood_init();
void get_neighborhood(int umbral, Image* image, int location, Neighborhood* neighborhood, int* visited);
int* get_4_neighbors(int umbral, Image* image, int location);
void get_neighbor(int umbral, Image* image, int i, int j, int* neighbors, int position);
void add_neighbor(Image* image, Neighborhood* neighborhood, int* visited, int neighbor_location);