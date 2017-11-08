#include "parse_csv.h" 

object* fill_scene(char* filename){
	FILE* fh = fopen(filename, "r");
	char line[256];
	int line_count = 0;
	object* m_scene = malloc(sizeof(object)*num_objects(filename));
	for (int line_count = 0; fgets(line, sizeof(line), fh); line_count++) {
		sscanf(line, "%[a-z]", m_scene[line_count].kind);
		if(strcmp(m_scene[line_count].kind, "camera") == 0){
			sscanf(line, "%[a-z], width: %lf, height: %lf", m_scene[line_count].kind, &m_scene[line_count].width, &m_scene[line_count].height);
		}
		if(strcmp(m_scene[line_count].kind, "sphere") == 0){
			m_scene[line_count].color = malloc(sizeof(double)*3);
			m_scene[line_count].position = malloc(sizeof(double)*3);
			sscanf(line, "%[a-z], color: [%lf, %lf, %lf], position: [%lf, %lf, %lf], radius: %i", 
					m_scene[line_count].kind, 
					&m_scene[line_count].color[0], &m_scene[line_count].color[1], &m_scene[line_count].color[2],
					&m_scene[line_count].position[0], &m_scene[line_count].position[1], &m_scene[line_count].position[2],
					&m_scene[line_count].radius);
			m_scene[line_count].color[0] = 255*m_scene[line_count].color[0];
			m_scene[line_count].color[1] = 255*m_scene[line_count].color[1];
			m_scene[line_count].color[2] = 255*m_scene[line_count].color[2];
		}
		if(strcmp(m_scene[line_count].kind, "plane") == 0){
			m_scene[line_count].color = malloc(sizeof(double)*3);
			m_scene[line_count].position = malloc(sizeof(double)*3);
			m_scene[line_count].normal = malloc(sizeof(double)*3);
			sscanf(line, "%[a-z], color: [%lf, %lf, %lf], position: [%lf, %lf, %lf], normal: [%lf, %lf, %lf]", 
					m_scene[line_count].kind, 
					&m_scene[line_count].color[0], &m_scene[line_count].color[1], &m_scene[line_count].color[2],
					&m_scene[line_count].position[0], &m_scene[line_count].position[1], &m_scene[line_count].position[2],
					&m_scene[line_count].normal[0], &m_scene[line_count].normal[1], &m_scene[line_count].normal[2]);
			m_scene[line_count].color[0] = m_scene[line_count].color[0]*255;
			m_scene[line_count].color[1] = m_scene[line_count].color[1]*255;
			m_scene[line_count].color[2] = m_scene[line_count].color[2]*255;

		}
	}
	int i=1;
	//printf("kind: %f\n", m_scene[i].position[2]);
	//printf("Object #%i {kind: %s, width: %f, height: %f,\n\tposition: (x=%f y=%f z=%f), color: (r=%f g=%f b=%f),\n\tnormal: (x=%f y=%f z=%f)}\n",
	//		i, m_scene[i].kind, m_scene[i].width, m_scene[i].height, m_scene[i].position[0], m_scene[i].position[1], m_scene[i].position[2], 
	//		m_scene[i].color[0], m_scene[i].color[1], m_scene[i].color[2], m_scene[i].normal[0], m_scene[i].normal[1], m_scene[i].normal[2]);
	fclose(fh);
	return m_scene;
}


int num_objects(char* filename){
	FILE* fh = fopen(filename, "r");
	char line[256];
	int lines = 0;
	for(int line_count = 0; fgets(line, sizeof(line), fh); line_count++){
		lines++;
	}
	return lines;
}