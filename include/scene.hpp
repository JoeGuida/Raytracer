#ifndef RAYTRACER_SCENE_HPP
#define RAYTRACER_SCENE_HPP

#include <memory>
#include <vector>

#include "camera.hpp"
#include "canvas.hpp"
#include "lights.hpp"
#include "sphere.hpp"
#include "viewport.hpp"

class Scene {
private:
	Camera camera;
	Canvas canvas;
	Viewport viewport;
	std::vector<Light*> lights;
	std::vector<Sphere> spheres;

public:
	void add(Light* ambient_light) { lights.push_back(ambient_light); }
	void add(const Sphere& sphere) { spheres.push_back(sphere); }
	const Camera get_camera() const { return camera; }
	const Canvas get_canvas() const { return canvas; }
	const std::vector<Light*>& get_lights() const { return lights; }
	const Viewport get_viewport() const { return viewport; }
	const std::vector<Sphere>& get_spheres() const { return spheres; }

	Scene(const Camera& camera, const Canvas& canvas, const Viewport& viewport) : camera(camera), canvas(canvas), viewport(viewport) {}
	Scene(const Scene&) = default;
	Scene(Scene&&) = default;
	virtual ~Scene() = default;
};

#endif