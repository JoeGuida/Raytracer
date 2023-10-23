#ifndef RAYTRACER_HELPERS_HPP
#define RAYTRACER_HELPERS_HPP

#include <cmath>

constexpr float PI = 3.1415926f;

static bool compare_float(float a, float b, float epsilon = 0.005f)
{
	return (fabs(a - b) < epsilon);
}

static float degrees(float radians) {
	return radians * (180.0f / PI);
};

static float radians(float degrees) {
	return degrees * (PI / 180.0f);
}

#endif