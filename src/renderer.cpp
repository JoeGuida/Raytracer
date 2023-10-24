#include "renderer.hpp"

int Renderer::rays_cast = 0;
int Renderer::recursion_depth = 3;

vec3 BACKGROUND_COLOR(0.1f, 0.1f, 0.1f);

float Renderer::calculate_lighting(const Ray& ray, const Scene& scene, const RaycastHit& hit) {
	float ambient = 0.0f;
	float diffuse = 0.0f;
	float specular = 0.0f;

	for (Light* light : scene.get_lights()) {
		DirectionalLight* directional_light = dynamic_cast<DirectionalLight*>(light);
		PointLight* point_light = dynamic_cast<PointLight*>(light);

		if (dynamic_cast<AmbientLight*>(light))
			ambient += light->get_intensity();
		if (directional_light) {
			diffuse += light->get_intensity() * calculate_diffuse_lighting(
				hit.normals.first, 
				directional_light->get_direction() - hit.points.first);
			specular += light->get_intensity() * calculate_specular_reflections(
				hit.normals.first,
				hit.points.first - directional_light->get_direction(),
				normalize(ray.get_direction() - hit.points.first),
				hit.material.get_specularity());
		}
		if (point_light) {
			float distance = magnitude(point_light->get_position() - hit.points.first);
			if (distance > point_light->get_range())
				continue;

			diffuse += light->get_intensity() * point_light->get_attenuation(distance) * calculate_diffuse_lighting(
				hit.normals.first,
				normalize(point_light->get_position() - hit.points.first));
			specular += light->get_intensity() * point_light->get_attenuation(distance) * calculate_specular_reflections(
				hit.normals.first,
				normalize(hit.points.first - point_light->get_position()),
				normalize(ray.get_direction() - hit.points.first),
				hit.material.get_specularity());
		}
	}

	return ambient + diffuse + specular;
}

float Renderer::calculate_diffuse_lighting(const vec3& normal, const vec3& light_direction) {
	float diffuse = dot(normal, light_direction) / (magnitude(normal) * magnitude(light_direction));
	return std::max(0.0f, diffuse);
}

float Renderer::calculate_specular_reflections(const vec3& normal, const vec3& light_direction, const vec3& view_direction, float specularity) {
	vec3 r = reflect(light_direction, normal);
	float specular = dot(r, view_direction) / (magnitude(r) * magnitude(view_direction));
	return std::max(0.0f, std::powf(specular, specularity));
}

void Renderer::drop_ppm_image(std::ofstream& file, const Scene& scene) {
	Canvas canvas = scene.get_canvas();
	file.open(FileSystem::get_path("/img/image.ppm"));
	file << "P3\n" << canvas.get_width() << ' ' << canvas.get_height() << "\n255\n";
	for (int i = -canvas.get_height() / 2; i < canvas.get_height() / 2; i++) {
		for (int j = -canvas.get_width() / 2; j < canvas.get_width() / 2; j++) {
			vec3 color = BACKGROUND_COLOR;
			vec2 viewport_pos = canvas_to_viewport(canvas, scene.get_viewport(), j, i);
			vec3 view_direction = normalize(vec3(viewport_pos, scene.get_camera().get_direction().z));
			Ray view_ray(scene.get_camera().get_position(), view_direction);
			
			color = trace_ray(view_ray, scene, recursion_depth);
			color.x = clamp(color.x, 0.0f, 1.0f);
			color.y = clamp(color.y, 0.0f, 1.0f);
			color.z = clamp(color.z, 0.0f, 1.0f);


			int r = static_cast<int>(color.x * 255.999f);
			int g = static_cast<int>(color.y * 255.999f);
			int b = static_cast<int>(color.z * 255.999f);
			file << r << ' ' << g << ' ' << b << '\n';
		}
	}
	file.close();
}

bool Renderer::is_any_object_hit(const Ray& ray, const Scene& scene) {
	for (const Sphere& sphere : scene.get_spheres()) {
		rays_cast++;
		if (intersects(ray, sphere)) {
			return true;
		}
	}

	return false;
}

bool Renderer::raycast_scene(const Ray& ray, const Scene& scene, RaycastHit& hit) {
	float least_distance = INFINITY;
	bool is_object_hit = false;
	for (const Sphere& sphere : scene.get_spheres()) {
		rays_cast++;
		RaycastHit temp_hit;
		if (intersects(ray, sphere, temp_hit)) {
			is_object_hit = true;
			float distance = magnitude(ray.get_origin() - temp_hit.points.first);
			if (distance < least_distance) {
				least_distance = distance;
				hit = temp_hit;
			}
		}
	}

	return is_object_hit;
}

void Renderer::render(const Scene& scene) {
	std::ofstream file;
	spdlog::stopwatch sw;
	drop_ppm_image(file, scene);
	spdlog::info("render(): {:.5}s", sw);
	spdlog::info("Total Rays Cast: {}", rays_cast);
}

vec3 Renderer::trace_ray(const Ray& ray, const Scene& scene, int depth) {
	RaycastHit hit;
	vec3 color(0.0f);

	if (color == BACKGROUND_COLOR)
		return color;

	bool is_object_hit = raycast_scene(ray, scene, hit);
	if (is_object_hit) {
		//Ray reflect_ray = Ray(hit.points.first, reflect(ray.get_direction(), hit.normals.first));
		//trace_ray(reflect_ray, scene, --depth);
		float light_received = calculate_lighting(ray, scene, hit);
		color = light_received * hit.material.get_color();
	}

	return color;
}