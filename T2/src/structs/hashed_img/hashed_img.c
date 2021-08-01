#include <stdlib.h>
#include "hashed_img.h"


HashedImg* init_hashed_img(int position)
{
  HashedImg* hashedImg = malloc(sizeof(HashedImg));
  *hashedImg = (HashedImg) {
    .position = position,   // el pixel de mas a la derecha y mas arriba
    .next = NULL,
  };
  return hashedImg;
}

void destroy_hashed_imgs(HashedImg* hashedImg)
{
  HashedImg* current = hashedImg -> next;
  HashedImg* next;
  free(hashedImg);
  while (current)
  {
    next = current->next;
    free(current);
    current = next;
  }
}