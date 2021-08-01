#include <stdio.h>
#include <stdlib.h>
#include "hash_entry.h"

HashEntry* init_hash_entry()
{
  HashEntry* hashEntry = malloc(sizeof(HashEntry));
  *hashEntry = (HashEntry) {
    .head = NULL,
  };
  return hashEntry;
}

void destroy_hash_entry(HashEntry* hashEntry)
{
  if (hashEntry->head)
  {
    destroy_hashed_imgs(hashEntry->head);
  }  
  free(hashEntry);
}

void add_hashed_to_hash_entry(HashEntry* hashEntry, HashedImg* img)
{
  if (hashEntry->head)
  {
    img->next = hashEntry->head;
    hashEntry->head = img;
  }
  else
  {
    hashEntry->head = img;
  }
}

void print_entry(HashEntry* hashEntry)
{
  printf("\t\t");
  HashedImg* current = hashEntry -> head;
  while (current)
  {
    printf("%i, ", current->position);
    current = current->next;
  }
  printf("\n");
}