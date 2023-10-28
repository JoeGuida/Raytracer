#ifndef RAYTRACER_RAYCASTHIT_HPP
#define RAYTRACER_RAYCASTHIT_HPP

#include <utility>

#include "material.hpp"
#include "shape.hpp"
#include "vectors.hpp"

class RaycastHit {
public:
	Shape const* object;
	vec3 normal;
	vec3 point;

	RaycastHit& operator=(const RaycastHit& hit) {
		object = hit.object;
		normal = hit.normal;
		point = hit.point;
	}

	RaycastHit() : object(nullptr), normal(vec3(0.0f)), point(vec3(0.0f)) {}
	RaycastHit(Shape* object, const vec3& normal, const vec3& point) : object(object), normal(normal), point(point) {}
	RaycastHit(const RaycastHit&) = default;
	RaycastHit(RaycastHit&&) = default;
	virtual ~RaycastHit() = default;
};

#endif