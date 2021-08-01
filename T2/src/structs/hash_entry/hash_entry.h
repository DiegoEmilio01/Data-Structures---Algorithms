#pragma once

#include "../hashed_img/hashed_img.h"

typedef struct hash_entry
{
	HashedImg* head;
} HashEntry;

HashEntry* init_hash_entry();
void destroy_hash_entry(HashEntry* hashEntry);
void add_hashed_to_hash_entry(HashEntry* hashEntry, HashedImg* img);
void print_entry(HashEntry* hashEntry);