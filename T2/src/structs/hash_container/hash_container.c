#include <stdio.h>
#include <stdlib.h>
#include "hash_container.h"
#include "../subimg/subimg.h"

#define BLACK 0
#define WHITE 127
#define GREY 64

HashContainer* init_hash_container(int imgSize)
{
  HashContainer* hashContainer = malloc(sizeof(HashContainer));
  *hashContainer = (HashContainer) {
    .imgSize = imgSize,
    .size = imgSize - 2,
    .hashes = calloc(imgSize - 2, sizeof(Hash*)),
  };

  int pixels_quantity;
  int subimages_quantity;
  int minimum;
  for (int hash_id = 0; hash_id < hashContainer->size; hash_id++)
  {
    // cantidad de valores != de pixeles negros que puede tener ese hash
    pixels_quantity = (hash_id + 2) * (hash_id + 2) + 1; 
    // es la cantidad de subimagenes != en cuanto a posicion
    subimages_quantity = (hashContainer->imgSize - hash_id - 1) * (hashContainer->imgSize - hash_id - 1);
    minimum = (pixels_quantity < subimages_quantity) ? pixels_quantity : subimages_quantity;
    // printf("%i \n", minimum);
    hashContainer->hashes[hash_id] = init_hash(minimum);
  }
  return hashContainer;
}

void destroy_hash_container(HashContainer* hashContainer)
{
  for (int hash_id = 0; hash_id < hashContainer->size; hash_id++)
  {
    destroy_hash(hashContainer->hashes[hash_id]);
  }
  free(hashContainer->hashes);
  free(hashContainer);
}

void hash_image(HashContainer* hashContainer, int position, int img_size, int pixel_quantity)
{
  HashedImg* hashedImg = init_hashed_img(position);
  int hash_value = pixel_quantity % ((hashContainer->imgSize - img_size + 1) * (hashContainer->imgSize - img_size + 1));
  // printf("%i - %i\n", hash_value, hashContainer->hashes[img_size - 2]->size);
  add_hashed_to_hash(hashContainer->hashes[img_size - 2], hash_value, hashedImg);
}

HashedImg* hash_query(HashContainer* hashContainer, Image* query)
{
  int pixel_quantity = 0;
  int location;
  for (int j = 0; j < query->width; j++)
  {
    for (int i = 0; i < query->height; i++)
    {
      location = i * (query -> width) + j;
      if (!query->pixels[location]) pixel_quantity += 1;
    }
  }
  int hash_value = pixel_quantity % ((hashContainer->imgSize - query->height + 1) * (hashContainer->imgSize - query->height + 1));
  return hashContainer->hashes[query->height - 2]->entries[hash_value]->head;
}

void populate_hash_container(HashContainer* hashContainer, Image* image)
{
  SubImg* subImg;
  int full_subimage;
  int location;
  int value;
  for (int size = 2; size < image->height; size++)
  {
    for (int i = 0; i <= image->height - size; i++)
    {
      full_subimage = 0;
      subImg = init_sub_img(size);
      for (int j = 0; j <= image->width - 1; j++)
      {
        if (j == size - 1) full_subimage = 1;
        value = 0;
        for (int l_offset = 0; l_offset < size; l_offset++)
        {
          location = (i + l_offset) * (image -> width) + j;
          if (!image->pixels[location]) value += 1;
        }
        new_column_sub_img(subImg, value, j % size);
        // if (full_subimage) printf("t %i, i %i\n", subImg->total, i);
        if (full_subimage) hash_image(hashContainer, i * (image -> width) + j, size, subImg->total);
      }
      destroy_sub_img(subImg);
    }
  }
}

void print_hash_container(HashContainer* hashContainer)
{
  printf("\nEl tamaño de este hash container (#hashes) es: %i\n\n.", hashContainer->size);
  for (int hash_id = 0; hash_id < hashContainer->size; hash_id++)
  {
    printf("\n\tHash para imgs de tamaño: %i\n.", hash_id + 2);
    print_hash(hashContainer->hashes[hash_id]);
  }
}

int compare_subimg_and_query(int position, Image* query_image, Image* image)
{
  int location;
  int sublocation;
  int offset_j = (position % image->width) - query_image->width + 1;
  int offset_i = position / image->width;
  for (int j = 0; j < query_image->width; j++)
  {
    for (int i = 0; i < query_image->height; i++)
    {
      location = (i + offset_i) * (image->width) + (j + offset_j);
      sublocation = i * (query_image->width) + j;
      // printf("loc: %i %i\n", location, sublocation);
      if (image->pixels[location] != query_image->pixels[sublocation]) return 0;
    }
  }
  return 1;
}

void modify_output(int position, Image* query_image, Image* out_image)
{
  int location;
  int sublocation;
  int offset_j = (position % out_image->width) - query_image->width + 1;
  int offset_i = position / out_image->width;
  for (int j = 0; j < query_image->width; j++)
  {
    for (int i = 0; i < query_image->height; i++)
    {
      location = (i + offset_i) * (out_image->width) + (j + offset_j);
      sublocation = i * (query_image->width) + j;
      if (query_image->pixels[sublocation] == BLACK) out_image->pixels[location] = GREY;
    }
  }
}