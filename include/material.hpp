#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP

#include "vectors.hpp"

class Material {
private:
	vec3 color;

public:
	vec3 get_color() const { return color; }

	Material& operator=(const Material& mat) {
		color = mat.color;
		return *this;
	}

	Material(const vec3& color) : color(color) {}
	Material(const Material&) = default;
	Material(Material&&) = default;
	virtual ~Material() = default;
};

#endif