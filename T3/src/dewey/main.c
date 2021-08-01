#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../helpers/merge/merge.h"
#include "../structs/setContainer/setContainer.h"

int main(int argc, char** argv)
{
  // Revisamos los argumentos
  if(argc != 3) {
    printf("Modo de uso: %s <network.txt> <output.txt>\n", argv[0]);
    return 1;
  }

  FILE* input_file = fopen(argv[1], "r");

  int n_clients;
  int n_distributors;
  int n_routes;
  if (fscanf(input_file, "%d", &n_clients));
  if (fscanf(input_file, "%d", &n_distributors));
  if (fscanf(input_file, "%d", &n_routes));

  // int routes[n_routes][4];  // 0 el id, 1 es A, 2 es B y 3 el costo
  int* routes = calloc(n_routes, 4*sizeof(int));
  for (int route = 0; route < n_routes; route++)
  {
    routes[4*route] = route;
    if (fscanf(input_file, "%d", &routes[4*route+1]));
    if (fscanf(input_file, "%d", &routes[4*route+2]));
    if (fscanf(input_file, "%d", &routes[4*route+3]));
  }

  fclose(input_file);

  merge_sort(routes, n_routes);

  kruskal(n_clients, n_distributors, n_routes, routes, argv[2]);

  free(routes);
  return 0;
}