#include "set.h"

Set init_set(int parent)
{
  Set set;
  set.has_distributor = false;
  set.parent = parent;
  set.children = 1;
  return set;
}