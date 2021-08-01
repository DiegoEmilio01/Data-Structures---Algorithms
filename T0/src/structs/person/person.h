#pragma once

typedef struct person
{
  int _id;
  int state;
  struct person* parent;
  struct person* head;
  struct person* tail;
  struct person* prev;
  struct person* _next;
} Person;

Person* person_init(int _id, int state);
void append_contact(Person* person, int other_id, int state);
Person* search_contact(Person* person, int _id);
void recursive_inform(Person* person, int depth, FILE* output_file);
void person_destroy(Person* person);
void recursive_destroy(Person* person);
void recursive_statistics(Person* person, int* stats);
void state_update(Person* person, int state);