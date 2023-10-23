#include "renderer.hpp"

void Renderer::drop_ppm_image(std::ofstream& file, const Scene& scene) {
	Canvas canvas = scene.get_canvas();
	file.open(FileSystem::get_path("/img/image.ppm"));
	file << "P3\n" << canvas.get_width() << ' ' << canvas.get_height() << "\n255\n";
	for (int i = -canvas.get_height() / 2; i < canvas.get_height() / 2; i++) {
		for (int j = -canvas.get_width() / 2; j < canvas.get_width() / 2; j++) {
			float r = 0.0f;
			float g = 0.0f;
			float b = 0.0f;

			vec2 viewport_pos = canvas_to_viewport(canvas, scene.get_viewport(), j, i);
			vec3 view_direction = normalize(vec3(viewport_pos, scene.get_camera().get_direction().z));
			Ray view_ray(scene.get_camera().get_position(), view_direction);

			RaycastHit hit;
			for (const Sphere& sphere : scene.get_spheres()) {
				if (intersects(view_ray, sphere, hit))
					b = 1.0f;
			}

			int ir = static_cast<int>(255.999f * r);
			int ig = static_cast<int>(255.999f * g);
			int ib = static_cast<int>(255.999f * b);

			file << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}
	file.close();
}

void Renderer::render(const Scene& scene) {
	std::ofstream file;
	drop_ppm_image(file, scene);
}
