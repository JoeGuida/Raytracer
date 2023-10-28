#ifndef RAYTRACER_HELPERS_HPP
#define RAYTRACER_HELPERS_HPP

#include <cmath>

constexpr float PI = 3.1415926f;

static float clamp(float n, float min, float max) {
	if (n < min)
		return min;
	if (n > max)
		return max;

	return n;
}

static bool compare_float(float a, float b, float epsilon = 0.005f)
{
	return (fabs(a - b) < epsilon);
}

static float degrees(float radians) {
	return radians * (180.0f / PI);
};

template <typename T>
static T lerp(T a, T b, float t) {
	return a + (b - a) * t;
}

static float radians(float degrees) {
	return degrees * (PI / 180.0f);
}

#endif