#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../structs/world/world.h"


/* Retorna true si ambos strings son iguales */
bool string_equals(char *string1, char *string2)
{
  return !strcmp(string1, string2);
}

/* Revisa que los parametros del programa sean válidos */
bool check_arguments(int argc, char **argv)
{
  if (argc != 3)
  {
    printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
    printf("Donde:\n");
    printf("\tINPUT es la ruta del archivo de input\n");
    printf("\tOUTPUT es la ruta del archivo de output\n");
    return false;
  }

  return true;
}

int main(int argc, char **argv)
{
  /* Si los parámetros del programa son inválidos */
  if (!check_arguments(argc, argv))
  {
    /* Salimos del programa indicando que no terminó correctamente */
    return 1;
  }

  /* Abrimos el archivo de input */
  FILE *input_file = fopen(argv[1], "r");

  /* Abrimos el archivo de output */
  FILE *output_file = fopen(argv[2], "w");


  char command[32];
  
  /* Leemos la cantidad de países */
  int n_countries;
  fscanf(input_file, "%d", &n_countries);

  World* world = world_init(n_countries); // Implementado

  /* Leemos la cantidad de regiones de cada país */
  int n_regions;
  for (int cty = 0; cty < n_countries; cty++)
  {
    fscanf(input_file, "%d", &n_regions);
    
    create_region(world, cty, n_regions); // Implementado
  }

  /* Número de eventos/líneas */
  int n_lines;
  fscanf(input_file, "%d", &n_lines);

  /* Declaramos variables para guardar: 
    - Id de país.
    - Id de región. 
    - Profundidad.
    - Id de contacto para las rutas
    - Número de contactos.
  */

  int country_id;
  int region_id;
  int depth;
  int depth_one;
  int depth_two;
  int contact_id;
  int n_contacts;


  while (n_lines)
  {
    /* Disminuimos en 1 el número de líneas por leer */
    n_lines--;

    /* Leemos la instrucción */
    fscanf(input_file, "%s", command);

    /* Obtenemos país, región, y profundidad */
    fscanf(input_file, "%d", &country_id);
    fscanf(input_file, "%d", &region_id);
    

    /* POSITIVE */
    if (string_equals(command, "ADD_CONTACTS"))
    {
      fscanf(input_file, "%d", &depth);
      /* Obtenemos la ruta desde el archivo*/
      int* route = calloc(depth, sizeof(int));  // Implementado
      for (int r = 0; r < depth; r++)
      {
        fscanf(input_file, "%d", &contact_id);
        route[r] = contact_id;
      }
      /* Obtenemos el numero de contactos */
      fscanf(input_file, "%d", &n_contacts);
      // printf("ADD_CONTACTS %d %d %d %d\n", country_id, region_id, depth, n_contacts);
      add_contacts(world, country_id, region_id, depth, route, n_contacts); // Implementado
      free(route);
    } 
    else if (string_equals(command, "POSITIVE"))
    {

      fscanf(input_file, "%d", &depth);
      //printf("POSITIVE %d %d %d \n", country_id, region_id, depth);
      /* Obtenemos la ruta desde el archivo*/
      int* route = calloc(depth, sizeof(int));  // Implementado
      for (int r = 0; r < depth; r++)
      {
        fscanf(input_file, "%d", &contact_id);
        route[r] = contact_id;
      }
      positive(world, country_id, region_id, depth, route);  // Implementado
      free(route);
    } 
    else if (string_equals(command, "NEGATIVE"))
    {
      
      fscanf(input_file, "%d", &depth);
      // printf("NEGATIVE %d %d %d \n", country_id, region_id, depth);
      /* Obtenemos la ruta desde el archivo*/
      int* route = calloc(depth, sizeof(int));  // Implementado
      for (int r = 0; r < depth; r++)
      {
        fscanf(input_file, "%d", &contact_id);
        route[r] = contact_id;
      }
      negative(world, country_id, region_id, depth, route);  // Implementado
      free(route);
    } 
    else if (string_equals(command, "RECOVERED"))
    {
      
      fscanf(input_file, "%d", &depth);
      //printf("RECOVERED %d %d %d \n", country_id, region_id, depth);
      /* Obtenemos la ruta desde el archivo*/
      int* route = calloc(depth, sizeof(int));  // Implementado
      for (int r = 0; r < depth; r++)
      {
        fscanf(input_file, "%d", &contact_id);
        route[r] = contact_id;
      }
      recovered(world, country_id, region_id, depth, route);  // Implementado
      free(route);
    } 
    else if (string_equals(command, "CORRECT"))
    {
      fscanf(input_file, "%d", &depth_one);
      // printf("CORRECT %d %d %d \n", country_id, region_id, depth_one);
      /* Obtenemos la primera ruta desde el archivo*/
      int* route_one = calloc(depth_one, sizeof(int));  // Implementado
      for (int r = 0; r < depth_one; r++)
      {
        fscanf(input_file, "%d", &contact_id);
        route_one[r] = contact_id;
      }
      fscanf(input_file, "%d", &depth_two);
      /* Obtenemos la segunda ruta desde el archivo*/
      int* route_two = calloc(depth_two, sizeof(int));  // Implementado
      for (int r = 0; r < depth_two; r++)
      {
        fscanf(input_file, "%d", &contact_id);
        route_two[r] = contact_id;
      }
      correct(world, country_id, region_id, depth_one, route_one, depth_two, route_two);  // Implementado
      free(route_one);
      free(route_two);
    } 
    else if (string_equals(command, "INFORM"))
    {
      // fprintf(output_file, "INFORM %d %d\n", country_id, region_id);
      inform(world, country_id, region_id, output_file);
    } 
    else if (string_equals(command, "STATISTICS"))
    {
      // fprintf(output_file, "STATISTICS %d %d\n", country_id, region_id);
      statistics(world, country_id, region_id, output_file);  // Implementado

    }

  }

  world_destroy(world); // Implementado

  fclose(input_file);
  fclose(output_file);
  return 0;
}