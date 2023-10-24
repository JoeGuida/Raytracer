#ifndef RAYTRACER_RENDERER_HPP
#define RAYTRACER_RENDERER_HPP

#include <fstream>

#include "spdlog/spdlog.h"
#include "spdlog/stopwatch.h"

#include "filesystem.hpp"
#include "lights.hpp"
#include "scene.hpp"

class Renderer {
public:
	static int rays_cast;

	static float calculate_lighting(const Ray& ray, const Scene& scene, const RaycastHit& hit);
	static float calculate_diffuse_lighting(const vec3& normal, const vec3& light_direction);
	static float calculate_specular_reflections(const vec3& normal, const vec3& light_direction, const vec3& view_direction, float specularity);
	static void drop_ppm_image(std::ofstream& file, const Scene& scene);
	static bool get_closest_object_hit(const Ray& ray, const Scene& scene, RaycastHit& hit);
	static void render(const Scene& scene);

	Renderer() {}
	Renderer(const Renderer&) = default;
	Renderer(Renderer&&) = default;
	virtual ~Renderer() = default;
};

#endif