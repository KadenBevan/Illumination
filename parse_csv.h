#ifndef PARSE_CSV_H
#define PARSE_CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char kind[64];
	double radius;
	double width;
	double height;
	double* position;
	double* color;
	double* normal;
	double* diffuse_color; // The diffuse color of the object (vector)
	double* specular_color; // The specular color of the object (vector)
}stObject;

typedef struct{
	char kind[64];
	double* position; // The location of the light
	double* color; // The color of the light (vector)
	double radial_a0; // The lowest order term in the radial attenuation function (lights only)
	double radial_a1; // The middle order term in the radial attenuation function (lights only)
	double radial_a2; // The highest order term in the radial attenuation function (lights only)
	double theta; // The angle of the spotlight cone (spot lights only) in degrees;
	//If theta = 0 or is not present, the light is a point light;
	//Note that the C trig functions assume radians so you may need to do
	//a conversion.
	double angular_a0; // The exponent in the angular attenuation function (spot lights only)
	double* direction; // The direction vector of the spot light (spot lights only)
}stLight;

stLight* fill_lights(char* filename);
stObject* fill_scene(char* filename);
int add_camera(stObject* scene, char* line, int pos);
int add_sphere(stObject* scene, char* line, int pos);
int add_plane(stObject* scene, char* line, int pos);
int add_light(stLight* lights, char* line, int pos);
int num_objects(void);
int num_lights(void);

#endif