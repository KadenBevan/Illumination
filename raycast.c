#include "raycast.h"

static double cam_height;
static double cam_width;
static double img_height;
static double img_width;
static double pixels_width;
static double pixels_height;
static int object_count;
static int light_count;
static stObject* scene;

int main(int argc, char* argv[]){
	// check argument number
	if(argc < 5 || argc > 5) {
		printf("argc error");
		return -1;
	}

    // check input file
    char* fn_in = argv[3];
	if(strstr(fn_in, ".txt") == NULL){
		printf("The file provided is not .txt, Please see README.md for more details.");
		return -2;
	}
	// check output file
	char* fn_out = argv[4];
	if(strstr(fn_out, ".ppm") == NULL){
		printf("The file provided is not .ppm, Please see README.md for more details.");
		return -2;
	}
	// initialize variables
	scene = fill_scene(fn_in);
	if(!scene){ // check scene is not empty
		printf("Error reading objects");
		return -3;
	}
	if(!scene[0].width || !scene[0].width){ // check camera is 0 stObject
		printf("Error reading camera");
		return -4;
	}
	img_width = atof(argv[1]);
	img_height = atof(argv[2]);
	cam_width = scene[0].width;
	cam_height = scene[0].height;
	pixels_height = cam_height / img_height;
	pixels_width = cam_width / img_height;
	object_count = num_objects();
	light_count = num_lights();
	//printf("%f", scene[0].width);
	cast_rays(object_count, fn_out);
	free(scene);
}

int cast_rays(int count, char* file_out){
	double cx = 0;
	double cy = 0;
	FILE *fh_out = fopen(file_out, "wb");
	if(!fh_out){
		printf("ERROR");
		return -1;
	}
	fprintf(fh_out, "P3\n%i %i\n255\n", (int)img_width, (int)img_height);
	for(int i=0; i<img_height; i++){
		for(int j=0; j<img_width; j++){
			double color[3] = {82, 86, 89};
			double r0[3] = {0, 0, 0};
			double rd[3] =  {cx - (cam_width/2) + pixels_width * (j + 0.5), cy-(cam_height/2) + pixels_height * (i+0.5), 1};
			normalize_vector(rd);
			double closest_t = INFINITY;
			for(int k=1; k<count; k++){
				double t = 0;
				if(strcmp(scene[k].kind, "sphere") == 0){
					t = sphere_intersection(r0, rd, scene[k].position, scene[k].radius);
				}
				else if(strcmp(scene[k].kind, "plane") == 0){
					t = plane_intersection(r0, rd, scene[k].position, scene[k].normal);
				}
				if (t >= 0 && t < closest_t) {
					closest_t = t;
					color[0] = scene[k].color[0]*255;
					color[1] = scene[k].color[1]*255;
					color[2] = scene[k].color[2]*255;
				}
			}
			fprintf(fh_out, "%i %i %i ", (int)color[0], (int)color[1], (int)color[2]);
		}
	}
	fclose(fh_out);
}