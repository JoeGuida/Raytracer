#include "spdlog/spdlog.h"

#include "camera.hpp"
#include "canvas.hpp"
#include "lights.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "renderer.hpp"
#include "vectors.hpp"
#include "viewport.hpp"

constexpr int IMAGE_WIDTH = 1280;
constexpr int IMAGE_HEIGHT = 720;
constexpr float ASPECT_RATIO = static_cast<float>(IMAGE_WIDTH) / static_cast<float>(IMAGE_HEIGHT);

int main() {
	spdlog::set_level(spdlog::level::debug);

	// create the scene and camera
	spdlog::info("Setting up scene");
	Camera camera(vec3(0.0f, 0.0f, -10.0f), vec3(0.0f, 0.0f, 1000.0f));
	Canvas canvas(IMAGE_WIDTH, IMAGE_HEIGHT);
	Viewport viewport(ASPECT_RATIO, 1.0f);
	Scene scene(camera, canvas, viewport);

	// add a sphere to the scene
	spdlog::info("Adding items to scene");
	Sphere sphere(vec3(0.0f, 0.0f, 0.0f), 3.0f, Material(vec3(1.0f, 0.0f, 0.0f), 10000.0f));
	Sphere sphere1(vec3(5.0f, 0.0f, 0.0f), 1.5f, Material(vec3(0.0f, 0.0f, 1.0f), 15.0f));
	Sphere sphere2(vec3(-5.0f, 0.0f, 0.0f), 1.5f, Material(vec3(0.0f, 1.0f, 0.0f), 500.0f));
	scene.add(sphere);
	scene.add(sphere1);
	scene.add(sphere2);

	// add some lights to the scene
	AmbientLight* ambient_light = new AmbientLight(0.1f);
	DirectionalLight* directional_light = new DirectionalLight(0.2f, vec3(500.0f, 1000.0f, 1000.0f));
	PointLight* point_light = new PointLight(0.4f, vec3(0.0f, 0.0f, -5.0f), 32.0f);
	scene.add(ambient_light);
	scene.add(directional_light);
	scene.add(point_light);

	// render the scene
	spdlog::info("Rendering the scene");
	Renderer::render(scene);

	return 0;
}