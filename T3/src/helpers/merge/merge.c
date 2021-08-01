#include "./merge.h"
#include <stdlib.h>

// Merge Sort iterativo basado fuertemente en https://www.geeksforgeeks.org/iterative-merge-sort/

int min(int x, int y) { return (x<y)? x :y; } 

void merge_sort(int* routes,  int n_routes)
{
  for (int curr_size = 1; curr_size <= n_routes - 1; curr_size = 2*curr_size)
  {
    for (int left_start = 0; left_start < n_routes - 1; left_start += 2*curr_size)
    {
      int mid = min(left_start + curr_size - 1, n_routes - 1);
      int right_end = min(left_start + 2*curr_size - 1, n_routes - 1);
      merge(routes, left_start, mid, right_end);
    }
  }
}

void merge(int* routes, int l, int m, int r)
{
  int i, j, k;
  int n1 = m - l + 1;
  int n2 =  r - m;
  int* L = calloc(n1, 4*sizeof(int));
  int* R = calloc(n2, 4*sizeof(int));
  //int L[n1][4], R[n2][4]; // temp

  /* Copy data to temp arrays L[] and R[] */
  for (i = 0; i < n1; i++){
    L[4*i+0] = routes[4*(l + i)+0];
    L[4*i+1] = routes[4*(l + i)+1];
    L[4*i+2] = routes[4*(l + i)+2];
    L[4*i+3] = routes[4*(l + i)+3];
  }
  for (j = 0; j < n2; j++){
    R[4*j+0] = routes[4*(m + 1+ j)+0];
    R[4*j+1] = routes[4*(m + 1+ j)+1];
    R[4*j+2] = routes[4*(m + 1+ j)+2];
    R[4*j+3] = routes[4*(m + 1+ j)+3];
  }
  /* Merge the temp arrays back into arr[l..r]*/
  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2)
  {
    if (L[4*i+3] <= R[4*j+3])
    {
      routes[4*k+0] = L[4*i+0];
      routes[4*k+1] = L[4*i+1];
      routes[4*k+2] = L[4*i+2];
      routes[4*k+3] = L[4*i+3];
      i++;
    }
    else
    {
      routes[4*k+0] = R[4*j+0];
      routes[4*k+1] = R[4*j+1];
      routes[4*k+2] = R[4*j+2];
      routes[4*k+3] = R[4*j+3];
      j++;
    }
    k++;
  }
  /* Copy the remaining elements of L[], if there are any */
  while (i < n1)
  {
    routes[4*k+0] = L[4*i+0];
    routes[4*k+1] = L[4*i+1];
    routes[4*k+2] = L[4*i+2];
    routes[4*k+3] = L[4*i+3];
    i++;
    k++;
  }
  /* Copy the remaining elements of R[], if there are any */
  while (j < n2)
  {
    routes[4*k+0] = R[4*j+0];
    routes[4*k+1] = R[4*j+1];
    routes[4*k+2] = R[4*j+2];
    routes[4*k+3] = R[4*j+3];
    j++;
    k++;
  }
  free(L);
  free(R);
}