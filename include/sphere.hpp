#ifndef RAYTRACER_SPHERE_HPP
#define RAYTRACER_SPHERE_HPP

#include "ray.hpp"
#include "raycasthit.hpp"
#include "vectors.hpp"

class Sphere {
private:
	vec3 center;
	float radius;

public:
	vec3 get_center() const { return center; }
	float get_radius() const { return radius; }

	Sphere(const vec3& center, float radius) : center(center), radius(radius) {}
	Sphere(const Sphere&) = default;
	Sphere(Sphere&&) = default;
	virtual ~Sphere() = default;
};

bool intersects(const Ray& ray, const Sphere& sphere, RaycastHit& hit);

#endif