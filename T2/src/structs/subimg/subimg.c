#include <stdio.h>
#include <stdlib.h>
#include "subimg.h"


SubImg* init_sub_img(int columns)
{
 SubImg* subImg = malloc(sizeof(SubImg));
  *subImg = (SubImg) {
    .total = 0,
    .columns = calloc(columns, sizeof(int)),
  };
  return subImg;
}

void destroy_sub_img(SubImg* subImg)
{
  free(subImg->columns);
  free(subImg);
}

void new_column_sub_img(SubImg* subImg, int value, int column)
{
  subImg->total -= subImg->columns[column];
  subImg->total += value;
  subImg->columns[column] = value;
}