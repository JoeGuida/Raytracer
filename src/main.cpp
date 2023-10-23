#include "spdlog/spdlog.h"

#include "camera.hpp"
#include "canvas.hpp"
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
	Sphere sphere(vec3(0.0f), 1.0f, Material(vec3(1.0f, 0.0f, 1.0f)));
	scene.add(sphere);

	// render the scene
	spdlog::info("Rendering the scene");
	Renderer::render(scene);

	return 0;
}