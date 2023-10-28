#include "sphere.hpp"

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

bool intersects(const Ray& ray, const Sphere& sphere, std::array<RaycastHit*, 2>& hits) {
	std::array<float, 2> t;
	float r = sphere.get_radius();
	vec3 a = sphere.get_center() - ray.get_origin();
	vec3 b = project(a, ray.get_direction());
	vec3 e = a - b;
	float fSq = r * r - dot(e, e);

	if (fSq < 0.0f)
		return false;

	float f = sqrtf(fSq);
	t[0] = magnitude(b) - f;
	t[1] = magnitude(b) + f;

	for (int i = 0; i < t.size(); i++) {
		if (t[i] < 0.0f)
			continue;
		
		hits[i] = new RaycastHit;
		hits[i]->object = &sphere;
		hits[i]->normal = sphere.get_normal(ray.get_origin() + ray.get_direction() * t[i]);
		hits[i]->point = ray.get_origin() + ray.get_direction() * t[i];
	}

	return true;
}
