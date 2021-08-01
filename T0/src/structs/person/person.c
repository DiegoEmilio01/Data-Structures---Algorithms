#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"


Person* person_init(int _id, int state)
{
  Person* person = malloc(sizeof(Person));
  *person = (Person) {
    ._id = _id,
    .state = state,
    .parent = NULL,
    .head = NULL,
    .tail = NULL,
    .prev = NULL,
    ._next = NULL,
  };
  // printf("Person initialized!\n");
  return person;
}

void append_contact(Person* person, int other_id, int state)
{
  Person* contact = person_init(other_id, state);
  contact -> parent = person;
  if (! person -> head)
  {
    person -> head = contact;
  }
  else
  {
    contact -> prev = person -> tail;
    person -> tail -> _next = contact;
  }
  person -> tail = contact;
}


Person* search_contact(Person* person, int _id)
{
  Person* current = person -> head;
  while (current)
  {
    if (current -> _id == _id)
    {
      return current;
    }
    else
    {
      current = current -> _next;
    }
  }
  return NULL;
}

void recursive_inform(Person* person, int depth, FILE* output_file)
{
  int length = depth * 4 + 1;
  char indentation[length];
  for (int i = 0; i < length; i++)
  {
    indentation[i] = ' ';
  }

  indentation[length - 1] = '\0';

  fprintf(output_file, "%s%i:%i\n", indentation, person -> _id, person -> state);
  Person* current = person -> head;
  while (current)
  {
    recursive_inform(current, depth + 1, output_file);
    current = current -> _next;
  }
}

void person_destroy(Person* person)
{
  free(person);
}

void recursive_destroy(Person* person)
{
  Person* current = person -> head;
  while (current)
  {
    Person* next = current -> _next;
    recursive_destroy(current);
    current = next;
  }
  person_destroy(person);
}

void recursive_statistics(Person* person, int* stats)
{
  switch (person -> state)
  {
  case 0:
    stats[0]++;
    break;
  case 1:
    stats[1]++;
    break;
  case 2:
    stats[2]++;
    break;
  case 3:
    stats[3]++;
    break;
  default:
    printf("State error, wrong value detected.\n");
    break;
  }
  Person* current = person -> head;
  while (current)
  {
    recursive_statistics(current, stats);
    current = current -> _next;
  }
}

void state_update(Person* person, int state)
{
  person -> state = state;
}