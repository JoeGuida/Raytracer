#ifndef RAYTRACER_RAYCASTHIT_HPP
#define RAYTRACER_RAYCASTHIT_HPP

#include <utility>

#include "material.hpp"

class RaycastHit {
public:
	std::pair<float, float> points;
	Material material;

	RaycastHit() : material(Material(vec3(0.0f))) {}
	RaycastHit(const RaycastHit&) = default;
	RaycastHit(RaycastHit&&) = default;
	virtual ~RaycastHit() = default;
};

#endif