#pragma once

#include "../hash_entry/hash_entry.h"

typedef struct hash
{
	int size; // Valor n significa que entries va de 0 hasta n-1
	HashEntry** entries;
} Hash;

Hash* init_hash(int size);
void destroy_hash(Hash* hash);
void add_hashed_to_hash(Hash* hash, int hash_value, HashedImg* img);
void print_hash(Hash* hash);