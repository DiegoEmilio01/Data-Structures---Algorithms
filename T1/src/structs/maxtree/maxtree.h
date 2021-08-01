#pragma once

#include "../pixel/pixel.h"
#include "../imagelib/image.h"
#include "../neighborhood/neighborhood.h"

typedef struct maxtree
{
  int umbral;
  int area;
  Pixel* pixels;
  struct maxtree* parent;
  struct maxtree* head;
  struct maxtree* next;
} Maxtree;

Maxtree* maxtree_init(int umbral, int area);
Maxtree* add_child(Maxtree* maxtree, int umbral, int area);
void add_pixel(Maxtree* maxtree, int location);
void maxtree_destroy(Maxtree* maxtree);
void print_nodes(Maxtree* maxtree);
int min_array(int* array, int* valid_elements, int lenght);
void generate_tree(Maxtree* maxtree, Image* image, Neighborhood* neighborhood, int* visited, int* neigh_visited);
void read_tree(Maxtree* maxtree, Image* new_img);
void area_filter(Maxtree* maxtree, int min_area, int threshold);
void delta_filter(Maxtree* maxtree, float max_delta);