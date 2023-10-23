#ifndef RAYTRACER_RAY_HPP
#define RAYTRACER_RAY_HPP

#include "vectors.hpp"

class Ray {
private:
	vec3 origin;
	vec3 direction;

public:
	vec3 get_origin() const { return origin; }
	vec3 get_direction() const { return direction; }

	Ray(const vec3& origin, vec3 direction) : origin(origin), direction(normalize(direction)) {}
	Ray(const Ray&) = default;
	Ray(Ray&&) = default;
	virtual ~Ray() = default;
};

#endif