//
// Created by Gilberto Dougal on 4/23/21.
//
#include "shooting_range.hpp"

float angele(vector2f v0, vector2f v1)
{
	return static_cast<float >(1.f - std::atan((v1.x - v0.x)/(v1.y - v0.y)) * DEGREE_TO_RAD);
}

float lenght(vector2f v0, vector2f v1) {
	return sqrtf(powf((v1.x - v0.x), 2) + powf((v1.y - v0.y), 2));
}

vector2f	normalize(vector2f v, vector2f v1) {
	float len = lenght(v, v1);
	return {(v1.x - v.x)/len, (v1.y - v.y)/len};
}

float random_float(float min, float max) {
	return  (max - min) * ((((float) rand()) / (float) RAND_MAX)) + min ;
}
