#include "parse_csv.h" 

static int object_count = 0;
static int light_count = 0;

stObject* fill_scene(char* filename){
	//based on kind call add
	FILE* fh = fopen(filename, "r");
	char line[256];
	int line_count = 0;
	// allocate memory for scene.
	stObject* m_scene = malloc(sizeof(stObject)*128);
	for (line_count = 0; fgets(line, sizeof(line), fh); line_count++){
		sscanf(line, "%[a-zA-Z]", m_scene[line_count].kind);
		if(strcmp(m_scene[line_count].kind, "camera") == 0){
			if(add_camera(m_scene, line, line_count) < 0){
				printf("Error parsing scene file.");
			}
		}
		else if(strcmp(m_scene[line_count].kind, "plane") == 0){
			if(add_plane(m_scene, line, line_count) < 0){
				printf("Error parsing scene file.");
			}
		}
		else if(strcmp(m_scene[line_count].kind, "sphere") == 0){
			if(add_sphere(m_scene, line, line_count) < 0){
				printf("Error parsing scene file.");
			}
		}
		else if(strcmp(m_scene[line_count].kind, "light") == 0){
			line_count--;
		}
	}
	fclose(fh);
	object_count = line_count;
	return m_scene;
}

stLight* fill_lights(char* filename){
	//based on kind call add
	FILE* fh = fopen(filename, "r");
	char line[256];
	int line_count = 0;
	// allocate memory for scene.
	stLight* m_lights = malloc(sizeof(stLight)*128);
	for (line_count = 0; fgets(line, sizeof(line), fh); line_count++){
		sscanf(line, "%[a-zA-Z]", m_lights[line_count].kind);
		// if the line is a light
		if(strcmp(m_lights[line_count].kind, "light") == 0){
			// add the light to the light struct
			if(add_light(m_lights, line, line_count) < 0){
				printf("Error parsing scene file.");
			}
		}
		// if it wasnt a light keep the struct index on track
		else if(strcmp(m_lights[line_count].kind, "light") != 0){
			line_count--;
		}
	}
	light_count = line_count;
	fclose(fh);
	return m_lights;
}

int add_light(stLight* lights, char* line, int pos){
	// make each line the start of the attribute name
	char *pos_attr = strstr(line, "position:");
	char *color_attr = strstr(line, "color:");
	char *a0_attr = strstr(line, "radial-a0:");
	char *a1_attr = strstr(line, "radial-a1:");
	char *a2_attr = strstr(line, "radial-a2:");
	char *theta_attr = strstr(line, "theta:");
	char *ang_attr = strstr(line, "angular-a0:");
	char *dir_attr = strstr(line, "direction:");
	// if the attribute name exists in the line
	if(pos_attr != NULL){
		// allocate space for the attribute values
		lights[pos].position = malloc(sizeof(double)*3);
		// add the attributes return error if there was a missing value or something else went wrong
		if(sscanf(pos_attr+9,  " [%lf, %lf, %lf],", &lights[pos].position[0], &lights[pos].position[1], &lights[pos].position[2]) != 3){
			return -1;
		}
	}
	if(color_attr != NULL){
		lights[pos].color = malloc(sizeof(double)*3);
		if(sscanf(color_attr+6,  " [%lf, %lf, %lf],", &lights[pos].color[0], &lights[pos].color[1], &lights[pos].color[2]) != 3){
			return -1;
		}
	}
	if(a0_attr != NULL){
		if(sscanf(a0_attr+11,  "%lf", &lights[pos].radial_a0) != 1){
			return -1;
		}
	}
	if(a1_attr != NULL){
		if(sscanf(a1_attr+11,  "%lf", &lights[pos].radial_a1) != 1){
			return -1;
		}
	}
	if(a2_attr != NULL){
		if(sscanf(a2_attr+10,  "%lf", &lights[pos].radial_a2) != 1){
			return -1;
		}
	}
	if(theta_attr != NULL){
		if(sscanf(theta_attr+6,  "%lf", &lights[pos].theta) != 1){
			return -1;
		}
	}
	if(ang_attr != NULL){
		if(sscanf(ang_attr+11,  "%lf", &lights[pos].angular_a0) != 1){
			return -1;
		}
	}
	if(dir_attr != NULL){
		lights[pos].direction = malloc(sizeof(double)*3);
		if(sscanf(dir_attr+10,  " [%lf , %lf , %lf],", &lights[pos].direction[0], &lights[pos].direction[1], &lights[pos].direction[2]) != 3){
			return -1;
		}
	}
}

int add_camera(stObject* scene, char* line, int pos){
	char *width_attr = strstr(line, "width:");
	char *height_attr = strstr(line, "height:");
	if(sscanf(width_attr+6, " %lf", &scene[pos].width) != 1){
		return -1;
	}
	if(sscanf(height_attr+7, " %lf", &scene[pos].height) != 1){
		return -1;
	}
}

int add_sphere(stObject* scene, char* line, int pos){
	char *radius_attr = strstr(line, "radius:");
	char *diff_attr = strstr(line, "diffuse_color:");
	char *spec_attr = strstr(line, "specular_color:");
	char *pos_attr = strstr(line, "position:");
	char *color_attr = strstr(line, " color:");
	if(color_attr != NULL){
		scene[pos].color = malloc(sizeof(double)*3);
		if(sscanf(color_attr+7, " [%lf , %lf , %lf],", &scene[pos].color[0], &scene[pos].color[1], &scene[pos].color[2]) != 3){
			return -1;
		}
	}
	if(radius_attr != NULL){
		if(sscanf(radius_attr+8, " %lf", &scene[pos].radius) != 1){
			return -1;
		}
	}
	if(diff_attr != NULL){
		scene[pos].diffuse_color = malloc(sizeof(double)*3);
		if(sscanf(diff_attr+14, " [%lf , %lf , %lf],", &scene[pos].diffuse_color[0], &scene[pos].diffuse_color[1], &scene[pos].diffuse_color[2]) != 3){
			return -1;
		}
	}
	if(spec_attr != NULL){
		scene[pos].specular_color = malloc(sizeof(double)*3);
		if(sscanf(spec_attr+15, " [%lf , %lf , %lf],", &scene[pos].specular_color[0], &scene[pos].specular_color[1], &scene[pos].specular_color[2]) != 3){
			return -1;
		}
	}
	if(pos_attr != NULL){
		scene[pos].position = malloc(sizeof(double)*3);
		if(sscanf(pos_attr+9,  " [%lf , %lf , %lf],", &scene[pos].position[0], &scene[pos].position[1], &scene[pos].position[2]) != 3){
			return -1;
		}
	}
}

int add_plane(stObject* scene, char* line, int pos){
	char *normal_attr = strstr(line, "normal:");
	char *diff_attr = strstr(line, "diffuse_color:");
	char *spec_attr = strstr(line, "specular_color:");
	char *pos_attr = strstr(line, "position:");
	char *color_attr = strstr(line, " color:");
	if(color_attr != NULL){
		scene[pos].color = malloc(sizeof(double)*3);
		if(sscanf(color_attr+7, " [%lf , %lf , %lf],", &scene[pos].color[0], &scene[pos].color[1], &scene[pos].color[2]) != 3){
			return -1;
		}
	}
	if(normal_attr != NULL){
		scene[pos].normal = malloc(sizeof(double)*3);
		if(sscanf(normal_attr+8, " [%lf , %lf , %lf],", &scene[pos].normal[0], &scene[pos].normal[1], &scene[pos].normal[2]) != 3){
			return -1;
		}
	}
	if(diff_attr != NULL){
		scene[pos].diffuse_color = malloc(sizeof(double)*3);
		if(sscanf(diff_attr+14, " [%lf , %lf , %lf],", &scene[pos].diffuse_color[0], &scene[pos].diffuse_color[1], &scene[pos].diffuse_color[2]) != 3){
			return -1;
		}
	}
	if(spec_attr != NULL){
		scene[pos].specular_color = malloc(sizeof(double)*3);
		if(sscanf(spec_attr+15, " [%lf , %lf , %lf],", &scene[pos].specular_color[0], &scene[pos].specular_color[1], &scene[pos].specular_color[2]) != 3){
			return -1;
		}
	}
	if(pos_attr != NULL){
		scene[pos].position = malloc(sizeof(double)*3);
		if(sscanf(pos_attr+9,  " [%lf , %lf , %lf],", &scene[pos].position[0], &scene[pos].position[1], &scene[pos].position[2]) != 3){
			return -1;
		}
	}
	return 1;
}
// return number of objects in the scene file
// can only be called after fill_scene is successfully run
int num_objects(void){
	return object_count;
}
// return number of lights in the scene file
// can only be called after fill_lights is successfully run
int num_lights(void){
	return light_count;
}