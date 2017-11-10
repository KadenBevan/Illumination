#include "vec_mathlib.h"

double normalize_vector(double* v) {
	double len = sqrt(pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2));
	v[0] /= len;
	v[1] /= len;
	v[2] /= len;
	return len;
}

double dot_vector(double* v1, double* v2){
	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

void scale_vector(double* v, double s, double* out) {
  out[0] = s * v[0];
  out[1] = s * v[1];
  out[2] = s * v[2];
}
void add_vector(double* v1, double* v2, double* out) {
  out[0] = v1[0] + v1[0];
  out[1] = v1[1] + v1[1];
  out[2] = v1[2] + v1[2];
}
void sub_vector(double* v1, double* v2, double* out) {
  out[0] = v1[0] - v2[0];
  out[1] = v1[1] - v2[1];
  out[2] = v1[2] - v2[2];
}

double sphere_intersection(double* ro, double* rd, double* center, double radius){
	double a = (pow(rd[0], 2) + pow(rd[1], 2) + pow(rd[2], 2));
	double b = (2 * (ro[0] * rd[0] - rd[0] * center[0] + ro[1] * rd[1] - rd[1] * center[1] + ro[2] * rd[2] - rd[2] * center[2]));
	double c = pow(ro[0], 2) - 2*ro[0]*center[0] + pow(center[0], 2) + ro[1] - 2*ro[1]*center[1] + pow(center[1], 2) + pow(ro[2], 2) - 2*ro[2]*center[2] + pow(center[2], 2) - pow(radius, 2);
	
	double disc = pow(b, 2) - (4 * a * c);
	if (disc < 0){ 
		return -1;
	}
	else{
		disc = sqrt(disc);
		double t0 = (-b - disc) / (2*a);
		double t1 = (-b + disc) / (2*a);
		if (t0 > 0)
			return t0;
		else if(t1 > 0)
			return t1;
	}
	return -1;
}

double plane_intersection(double* ro, double* rd, double* position, double* normal){
	double numer;
	double denom;
	double v[3];
	sub_vector(position, ro, v);
	numer = dot_vector(normal, v);
	denom = dot_vector(normal, rd);

	return numer/denom;
}

double radial_attin(double dist, double a0, double a1, double a2){
	if(a0 < 1e-10 && a1 < 1e-10 && a2 < 1e-10){
		return 1.0;
	}
	if(dist == INFINITY){
		return 1.0;
	}
	else{
		return 1/(pow(dist, 2) + (a1 * dist) + a0);
	}
}

double angular_attin(double a0, double theta, double* direction, double* light){
	double alpha = cos(dot_vector(light, direction));
	// convert alpha to degrees
	alpha = alpha * (180.0 / PI);
	// if theta is 0
	if(theta < 1e-10){
		return 1.0;
	}
	else if(theta < alpha){
		return 0.0;
	}
	else{
		return(pow(dot_vector(light, direction), a0));
	}
}



