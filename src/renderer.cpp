#include "renderer.hpp"

void Renderer::drop_ppm_image(std::ofstream& file, const Scene& scene) {
	Canvas canvas = scene.get_canvas();
	file.open(FileSystem::get_path("/img/image.ppm"));
	file << "P3\n" << canvas.get_width() << ' ' << canvas.get_height() << "\n255\n";
	for (int i = -canvas.get_height() / 2; i < canvas.get_height() / 2; i++) {
		for (int j = -canvas.get_width() / 2; j < canvas.get_width() / 2; j++) {

			vec3 color(0.0f);
			vec2 viewport_pos = canvas_to_viewport(canvas, scene.get_viewport(), j, i);
			vec3 view_direction = normalize(vec3(viewport_pos, scene.get_camera().get_direction().z));
			Ray view_ray(scene.get_camera().get_position(), view_direction);

			RaycastHit hit;
			for (const Sphere& sphere : scene.get_spheres()) {
				if (intersects(view_ray, sphere, hit))
					color = hit.material.get_color();
			}

			int r = static_cast<int>(color.x * 255.999f);
			int g = static_cast<int>(color.y * 255.999f);
			int b = static_cast<int>(color.z * 255.999f);
			file << r << ' ' << g << ' ' << b << '\n';
		}
	}
	file.close();
}

void Renderer::render(const Scene& scene) {
	std::ofstream file;
	spdlog::stopwatch sw;
	drop_ppm_image(file, scene);
	spdlog::debug("Renderer::render {:.5}s", sw);
}
