#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP

#include "vectors.hpp"

class Material {
public:
	vec3 color;
	float reflectivity;
	float specularity;

	Material(const vec3& color, float reflectivity, float specularity) : 
		color(color), 
		reflectivity(reflectivity), 
		specularity(specularity) {}
	Material(const Material&) = default;
	Material(Material&&) = default;
	virtual ~Material() = default;
};

#endif