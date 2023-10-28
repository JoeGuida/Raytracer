#ifndef RAYTRACER_SHAPE_HPP
#define RAYTRACER_SHAPE_HPP

#include "material.hpp"
#include "vectors.hpp"

class Shape {
public:
	virtual Material get_material() const = 0;
	virtual vec3 get_normal(const vec3& point) const = 0;
};

#endif