#ifndef PARSE_CSV_H
#define PARSE_CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char kind[64];
	int radius;
	double width;
	double height;
	double* position;
	double* color;
	double* normal;
}object;

object* fill_scene(char* filename);
int num_objects(char* filename);

#endif