#ifndef RAYTRACER_RENDERER_HPP
#define RAYTRACER_RENDERER_HPP

#include <fstream>

#include "spdlog/spdlog.h"
#include "spdlog/stopwatch.h"

#include "filesystem.hpp"
#include "scene.hpp"

class Renderer {
public:
	static void drop_ppm_image(std::ofstream& file, const Scene& scene);
	static void render(const Scene& scene);

	Renderer() {}
	Renderer(const Renderer&) = default;
	Renderer(Renderer&&) = default;
	virtual ~Renderer() = default;
};

#endif