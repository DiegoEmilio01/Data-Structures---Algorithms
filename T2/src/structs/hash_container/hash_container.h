#pragma once

#include "../hash/hash.h"
#include "../../imagelib/image.h"

typedef struct hash_container
{
	int imgSize;		// tamaño de la foto original
	int size;				// hay tamaño_imagen - 2 hashes
	Hash** hashes;	// para acceder a su hash, es el tamaño de la subimagen menos 2
} HashContainer;

HashContainer* init_hash_container(int imgSize);
void destroy_hash_container(HashContainer* hashContainer);
void hash_image(HashContainer* hashContainer, int position, int img_size, int pixel_quantity);
HashedImg* hash_query(HashContainer* hashContainer, Image* query);
void populate_hash_container(HashContainer* hashContainer, Image* image);
void print_hash_container(HashContainer* hashContainer);
int compare_subimg_and_query(int position, Image* query_image, Image* image);
void modify_output(int position, Image* query_image, Image* out_image);