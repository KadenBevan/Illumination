#ifndef vec_mathlib_h
#define vec_mathlib_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double sphere_intersection(double* ro, double* rd, double* center, double radius);
double plane_intersection(double* ro, double* rd, double* position, double* normal);
double normalize_vector(double* v);

#endif