#pragma once


typedef struct subimg
{
	int total;		// almacena el total de la cantidad de pixeles negros
	int* columns;	// almacena la cantidad de pixeles negros por columnas
} SubImg;

SubImg* init_sub_img(int columns);
void destroy_sub_img(SubImg* subImg);
void new_column_sub_img(SubImg* subImg, int value, int column);