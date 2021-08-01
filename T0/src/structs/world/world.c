#include <stdio.h>
#include <stdlib.h>
#include "world.h"
#include "../person/person.h"


World* world_init(int n_countries)
{
  World* world = malloc(sizeof(World));
  *world = (World){
    .n_countries = n_countries,
    .n_regions_countries = calloc(n_countries, sizeof(int)),
    .countries = calloc(n_countries, sizeof(Person**)),
    .people_count = calloc(n_countries, sizeof(int*)),
  };
  // printf("World initialized!\n");
  return world;
}

void create_region(World* world, int idx, int amount)
{
  world -> n_regions_countries[idx] = amount;

  world -> countries[idx] = calloc(amount, sizeof(Person*));
  for (int region = 0; region < amount; region++)
  {
    Person* patient_zero = person_init(0, 2);
    world -> countries[idx][region] = patient_zero;
  }

  world -> people_count[idx] = calloc(amount, sizeof(int));
  for (int region = 0; region < amount; region++)
  {
    world -> people_count[idx][region] = 1;
  }
}

Person* search(World* world, int country, int region, int depth, int* route)
{
  Person* person = world -> countries[country][region];
  for (int idx = 0; idx < depth; idx++)
  {
    person = search_contact(person, route[idx]);
  }
  return person;
}

void add_contact(Person* person, int new_id)
{
  if (person -> state == 2)
  {
    append_contact(person, new_id, 1);
  }
  else
  {
    append_contact(person, new_id, 0);
  }
}

void add_contacts(World* world, int country, int region, int depth, int* route, int n_contacts)
{  
  Person* person = search(world, country, region, depth, route);

  for (int i = 0; i < n_contacts; i++)
  {
    int new_id = world -> people_count[country][region];
    add_contact(person, new_id);
    world -> people_count[country][region] ++;
  }
}

void inform(World* world, int country, int region, FILE* output_file)
{
  fprintf(output_file, "INFORM %i %i\n", country, region);
  Person* patient_zero = world -> countries[country][region];
  recursive_inform(patient_zero, 0, output_file);
}

void world_destroy(World* world)
{
  for (int country = 0; country < world -> n_countries; country++)
  {
    for (int region = 0; region < world -> n_regions_countries[country]; region++)
    {
      Person* patient_zero = world -> countries[country][region];
      recursive_destroy(patient_zero);
    }
    free(world -> people_count[country]);
    free(world -> countries[country]);
  }
  free(world -> n_regions_countries);
  free(world -> people_count);
  free(world -> countries);
  free(world);
}

void statistics(World* world, int country, int region, FILE* output_file)
{
  fprintf(output_file, "STATISTICS %i %i\n", country, region);
  Person* patient_zero = world -> countries[country][region];
  int* stats = calloc(4, sizeof(int));
  recursive_statistics(patient_zero, stats);
  fprintf(output_file, "0:%i\n", stats[0]);
  fprintf(output_file, "1:%i\n", stats[1]);
  fprintf(output_file, "2:%i\n", stats[2]);
  fprintf(output_file, "3:%i\n", stats[3]);
  free(stats);
}

void recovered(World* world, int country, int region, int depth, int* route)
{
  Person* person = search(world, country, region, depth, route);
  state_update(person, 3);
}

void positive(World* world, int country, int region, int depth, int* route)
{
  Person* person = search(world, country, region, depth, route);
  state_update(person, 2);
  Person* current = person -> head;
  while (current)
  {
    state_update(current, 1);
    current = current -> _next;
  }
}

void negative(World* world, int country, int region, int depth, int* route)
{
  Person* person = search(world, country, region, depth, route);
  Person* parent = person -> parent;
  Person* prev = person -> prev;
  Person* next = person -> _next;
  if (parent -> head == person && parent -> tail == person)
  {
    parent -> head = NULL;
    parent -> tail = NULL;
  }
  else if (parent -> head == person)
  {
    parent -> head = next;
    next -> prev = NULL;
  }
  else if (parent -> tail == person)
  {
    parent -> tail = prev;
    prev -> _next = NULL;
  }
  else
  {
    prev -> _next = next;
    next -> prev = prev;
  }
  recursive_destroy(person);
}

void correct(World* world, int country, int region, int depth_one, int* route_one, int depth_two, int* route_two)
{
  Person* person_one = search(world, country, region, depth_one, route_one);
  Person* person_two = search(world, country, region, depth_two, route_two);
  Person* head_one = person_one -> head;
  Person* tail_one = person_one -> tail;
  person_one -> head = person_two -> head;
  person_one -> tail = person_two -> tail;
  Person* current = person_one -> head;
  while (current)
  {
    current -> parent = person_one;
    if (person_one -> state == 2 && current -> state == 0)
    {
      state_update(current, 1);
    }
    current = current -> _next;
  }
  person_two -> head = head_one;
  person_two -> tail = tail_one;
  current = person_two -> head;
  while (current)
  {
    current -> parent = person_two;
    if (person_two -> state == 2 && current -> state == 0)
    {
      state_update(current, 1);
    }
    current = current -> _next;
  }
}