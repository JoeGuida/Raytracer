#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP

#include "vectors.hpp"

class Material {
private:
	vec3 color;
	float specularity;

public:
	vec3 get_color() const { return color; }
	float get_specularity() const { return specularity; }

	Material& operator=(const Material& mat) {
		color = mat.color;
		specularity = mat.specularity;
		return *this;
	}

	Material(const vec3& color, float specularity) : color(color), specularity(specularity) {}
	Material(const Material&) = default;
	Material(Material&&) = default;
	virtual ~Material() = default;
};

#endif