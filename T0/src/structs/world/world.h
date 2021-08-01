#pragma once
#include "../person/person.h"

typedef struct world
{
  int n_countries;
  int* n_regions_countries;
  Person*** countries;
  int** people_count;
} World;

World* world_init(int n_countries);
void create_region(World* world, int idx, int amount);
Person* search(World* world, int country, int region, int depth, int* route);
void add_contact(Person* person, int new_id);
void add_contacts(World* world, int country, int region, int depth, int* route, int n_contacts);
void inform(World* world, int country, int region, FILE* output_file);
void statistics(World* world, int country, int region, FILE* output_file);
void world_destroy(World* world);
void recovered(World* world, int country, int region, int depth, int* route);
void positive(World* world, int country, int region, int depth, int* route);
void negative(World* world, int country, int region, int depth, int* route);
void correct(World* world, int country, int region, int depth_one, int* route_one, int depth_two, int* route_two);
