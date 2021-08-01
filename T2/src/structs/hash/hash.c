#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

Hash* init_hash(int size)
{
  Hash* hash = malloc(sizeof(Hash));
  *hash = (Hash) {
    .size = size,
    .entries = calloc(size, sizeof(HashEntry*)),
  };

  for (int hash_value = 0; hash_value < hash->size; hash_value++)
  {
    hash->entries[hash_value] = init_hash_entry();
  }
  return hash;
}

void destroy_hash(Hash* hash)
{
  for (int hash_value = 0; hash_value < hash->size; hash_value++)
  {
    destroy_hash_entry(hash->entries[hash_value]);
  }
  free(hash->entries);
  free(hash);
}

void add_hashed_to_hash(Hash* hash, int hash_value, HashedImg* img)
{
  add_hashed_to_hash_entry(hash->entries[hash_value], img);
}

void print_hash(Hash* hash)
{
  printf("\tEl tamaño de este hash (#entradas) es: %i\n\n.\tLas entradas son:\n", hash->size);
  for (int hash_value = 0; hash_value < hash->size; hash_value++)
  {
    print_entry(hash->entries[hash_value]);
  }
}