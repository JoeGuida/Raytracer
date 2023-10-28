#ifndef RAYTRACER_SPHERE_HPP
#define RAYTRACER_SPHERE_HPP

#include <array>

#include "material.hpp"
#include "ray.hpp"
#include "raycasthit.hpp"
#include "shape.hpp"
#include "vectors.hpp"

class Sphere : public Shape {
private:
	vec3 center;
	float radius;
	Material material;

public:
	vec3 get_center() const { return center; }
	float get_radius() const { return radius; }
	Material get_material() const override { return material; }
	vec3 get_normal(const vec3& point) const override { return normalize(point - center); }

	Sphere(const vec3& center, float radius, const Material& material) : center(center), radius(radius), material(material) {}
	Sphere(const Sphere&) = default;
	Sphere(Sphere&&) = default;
	virtual ~Sphere() = default;
};

bool intersects(const Ray& ray, const Sphere& sphere);
bool intersects(const Ray& ray, const Sphere& sphere, std::array<RaycastHit*, 2>& hits);

#endif