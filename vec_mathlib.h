#ifndef vec_mathlib_h
#define vec_mathlib_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "parse_csv.h"

#define PI 3.14159265

double sphere_intersection(double* ro, double* rd, double* center, double radius);
double plane_intersection(double* ro, double* rd, double* position, double* normal);

double normalize_vector(double* v);
double* surface_normal(stObject object);
double dot_vector(double* v1, double* v2);
void sub_vector(double* v1, double* v2, double* out);
void add_vector(double* v1, double* v2, double* out);
void scale_vector(double* v, double s, double* out);

double angular_attin(double a0, double theta, double* direction, double* light);
double radial_attin(double dist, double a0, double a1, double a2);

#endif