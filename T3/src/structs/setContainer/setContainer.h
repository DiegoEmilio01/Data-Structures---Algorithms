#pragma once

#include "../set/set.h"

Set* init_set_container(int size);
int find(Set* setContainer, int set);
void kruskal(int n_clients, int n_distributors, int n_routes, int* routes, char* output);