#ifndef RAYTRACER_RAYCASTHIT_HPP
#define RAYTRACER_RAYCASTHIT_HPP

#include <utility>

#include "material.hpp"

class RaycastHit {
public:
	std::pair<vec3, vec3> normals;
	std::pair<vec3, vec3> points;
	Material material;

	RaycastHit& operator=(const RaycastHit& hit) {
		normals = hit.normals;
		points = hit.points;
		material = hit.material;
		return *this;
	}

	RaycastHit() : material(Material(vec3(0.0f), 0.0f)), normals({vec3(0.0f), vec3(0.0f)}), points({ vec3(0.0f), vec3(0.0f) }) {}
	RaycastHit(const RaycastHit&) = default;
	RaycastHit(RaycastHit&&) = default;
	virtual ~RaycastHit() = default;
};

#endif