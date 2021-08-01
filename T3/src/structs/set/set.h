#pragma once
#include <stdbool.h>

typedef struct set
{
	bool has_distributor;
	int parent;
	int children;
} Set;

Set init_set(int position);