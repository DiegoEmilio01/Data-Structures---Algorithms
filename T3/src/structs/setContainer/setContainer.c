#include "setContainer.h"
#include <stdlib.h>
#include <stdio.h>

Set* init_set_container(int size)
{
  Set* setContainer = malloc(size*sizeof(Set));
  for (int set_id = 0; set_id < size; set_id++)
  {
    setContainer[set_id] = init_set(set_id);
  }
  return setContainer;
}

int find(Set* setContainer, int set)
{
  int new_set = setContainer[set].parent;
  while (set != new_set)
  {
    set = new_set;
    new_set = setContainer[set].parent;
  }
  return set;
}

// routes already sorted
void kruskal(int n_clients, int n_distributors, int n_routes, int* routes, char* output)
{
  Set* setContainer = init_set_container(n_clients); // init basic sets

  int n_connected = 0;
  int route_index;
  int route_id;
  int A;
  int A_set;
  int B;
  int B_set;
  int cost;

  int total_cost = 0;
  int n_solution = 0;
  int solution[n_clients + n_distributors];

  for (route_index = 0; route_index < n_routes && n_connected < n_clients; route_index++)
  {
    route_id = routes[4*route_index+0];
    A = routes[4*route_index+1];
    B = routes[4*route_index+2];
    cost = routes[4*route_index+3];
    if (A < n_clients && B < n_clients)
    {
      A_set = find(setContainer, A);
      B_set = find(setContainer, B);
      if (A_set == B_set) continue;
      if (setContainer[A_set].has_distributor && setContainer[B_set].has_distributor) continue;
      if (setContainer[A_set].has_distributor){
        setContainer[B_set].has_distributor = true;
        n_connected += setContainer[B_set].children;
      }
      else if (setContainer[B_set].has_distributor){
        setContainer[A_set].has_distributor = true;
        n_connected += setContainer[A_set].children;
      }
      if (setContainer[A_set].children > setContainer[B_set].children)
      {
        setContainer[B_set].parent = A_set;
        setContainer[A_set].children += setContainer[B_set].children;
      }
      else
      {
        setContainer[A_set].parent = B_set;
        setContainer[B_set].children += setContainer[A_set].children;
      }
      total_cost += cost;
      solution[n_solution] = route_id;
      n_solution ++;
    }
    else if (A < n_clients && B >= n_clients)
    {
      A_set = find(setContainer, A);
      if (!setContainer[A_set].has_distributor)
      {
        setContainer[A_set].has_distributor = true;
        n_connected += setContainer[A_set].children;
        total_cost += cost;
        solution[n_solution] = route_id;
        n_solution ++;
      }
    }
    else if (A >= n_clients && B < n_clients)
    {
      B_set = find(setContainer, B);
      if (!setContainer[B_set].has_distributor)
      {
        setContainer[B_set].has_distributor = true;
        n_connected += setContainer[B_set].children;
        total_cost += cost;
        solution[n_solution] = route_id;
        n_solution ++;
      }
    }
  }
  free(setContainer);
  FILE* output_file = fopen(output, "w");
  fprintf(output_file, "%i\n", total_cost);
  for (int solution_element = 0; solution_element < n_solution; solution_element++)
    fprintf(output_file, "%i\n", solution[solution_element]);
  fclose(output_file);
}