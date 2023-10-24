#include "sphere.hpp"

bool intersects(const Ray& ray, const Sphere& sphere, RaycastHit& hit) {
	float r = sphere.get_radius();
	vec3 a = sphere.get_center() - ray.get_origin();
	vec3 b = project(a, ray.get_direction());
	vec3 e = a - b;
	float fSq = r * r - dot(e, e);

	if (fSq < 0.0f)
		return false;

	float f = sqrtf(fSq);
	float t1 = magnitude(b) - f;
	float t2 = magnitude(b) + f;

	if (t1 < 0.0f)
		t1 = INFINITY;
	if (t2 < 0.0f)
		t2 = INFINITY;

	hit.points = { ray.get_origin() + ray.get_direction() * t1, ray.get_origin() + ray.get_direction() * t2 };
	hit.material = sphere.get_material();
	hit.normals = {
		sphere.get_normal(ray.get_origin() + ray.get_direction() * t1),
		sphere.get_normal(ray.get_origin() + ray.get_direction() * t2)
	};

	return true;
}

bool intersects(const Ray& ray, const Sphere& sphere) {
	float r = sphere.get_radius();
	vec3 a = sphere.get_center() - ray.get_origin();
	vec3 b = project(a, ray.get_direction());
	vec3 e = a - b;
	float fSq = r * r - dot(e, e);

	if (fSq < 0.0f)
		return false;

	return true;
}