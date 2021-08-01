#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../structs/imagelib/image.h"
#include "../structs/maxtree/maxtree.h"
#include "../structs/neighborhood/neighborhood.h"

int main(int argc, char** argv)
{
    // Revisamos los argumentos
    if(argc < 4) {
        printf("Modo de uso: %s <input.png> <output.png> <command> [args]\n", argv[0]);
        return 1;
    }

    // Cargamos la imagen original desde el archivo
    Image* image = img_png_read_from_file(argv[1]);
    
    int root_umbral = 0;
    
    Neighborhood* neighborhood = neighborhood_init();
    int* neigh_visited = calloc(image -> pixel_count, sizeof(int));
    get_neighborhood(root_umbral, image, 0, neighborhood, neigh_visited);
    free(neigh_visited);

    int* recursive_visited = calloc(image -> pixel_count, sizeof(int));
    int* recursive_neigh_visited = calloc(image -> pixel_count, sizeof(int));

    Maxtree* maxtree = maxtree_init(neighborhood -> min_umbral, neighborhood -> area);
    generate_tree(maxtree, image, neighborhood, recursive_visited, recursive_neigh_visited);

    pixel_destroy(neighborhood -> pixels);
    free(neighborhood);
    
    free(recursive_visited);
    free(recursive_neigh_visited);

    //print_nodes(maxtree);
    
    // Creamos una nueva imagen de igual tamaño, para el output
    Image* new_img = calloc(1, sizeof(Image));
    *new_img = (Image) {
        .height = image->height,
        .width = image->width,
        .pixel_count = image->pixel_count,
        .pixels = calloc(image->pixel_count, sizeof(int))
    };

    // Filtramos el arbol y lo guardamos en la imagen, segun el filtro que corresponda
    if (! strcmp("delta", argv[3]))
    {
        // Filtro DELTA
        float max_delta = atof(argv[4]);
        delta_filter(maxtree, max_delta);
    }
    else if (! strcmp("area", argv[3]))
    {
        // Filtro AREA-COLOR
        int min_area = atoi(argv[4]);
        int threshold = atoi(argv[5]);
        area_filter(maxtree, min_area, threshold);
    }

    read_tree(maxtree, new_img);

    // Exportamos la nueva imagen
    printf("Guardando imagen en %s\n", argv[2]);
    img_png_write_to_file(new_img, argv[2]);
    printf("Listo!\n");

    // Liberamos los recursos
    img_png_destroy(image);
    img_png_destroy(new_img);

    maxtree_destroy(maxtree);

    // Terminamos exitosamente
    return 0;
}
