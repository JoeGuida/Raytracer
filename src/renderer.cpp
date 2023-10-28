#include "renderer.hpp"

int Renderer::rays_cast = 0;
int Renderer::recursion_depth = 3;
int Renderer::supersampling_levels = 0;
float Renderer::bias = 0.0001f;

const vec3 BACKGROUND_COLOR(0.5f, 0.5f, 0.5f);

/*
calculates the lighting at a hit point
calculates lighting from all lights in the scene 
returns a float in the range [0.0, 1.0] indicating the amount of light received
*/
float Renderer::calculate_lighting(const Ray& ray, const Scene& scene, const RaycastHit& hit) {
	float ambient = 0.0f;
	float diffuse = 0.0f;
	float specular = 0.0f;

	for (Light* light : scene.get_lights()) {
		AmbientLight* ambient_light = dynamic_cast<AmbientLight*>(light);
		DirectionalLight* directional_light = dynamic_cast<DirectionalLight*>(light);
		PointLight* point_light = dynamic_cast<PointLight*>(light);

		// continue if ambient light since no further calculation is needed
		if (ambient_light) {
			ambient += light->get_intensity();
			continue;
		}

		// Determine the light direction and intensity
		vec3 light_direction(0.0f);
		float intensity = 0.0f;
		if (directional_light) {
			light_direction = normalize(directional_light->get_direction() - hit.point);
			intensity = light->get_intensity();
		}
		if (point_light) {
			float distance = magnitude(point_light->get_position() - hit.point);
			light_direction = normalize(point_light->get_position() - hit.point);
			if (distance > point_light->get_range()) {
				intensity = 0.0f;
			}
			else {
				intensity = light->get_intensity() * point_light->get_attenuation(distance);
			}
		}

		// Do not calculate diffuse specular lighting for this light if the point is in shadow
		Ray shadow_ray(hit.point + hit.normal * bias, light_direction);
		if (is_any_object_hit(shadow_ray, scene, hit.object))
			continue;

		// If point is not in shadow, calculate diffuse and specular lighting
		diffuse += intensity * calculate_diffuse_lighting(hit.normal, light_direction);
		specular += intensity * calculate_specular_reflections(
			hit.normal, 
			light_direction, 
			ray.get_direction(), 
			hit.object->get_material().specularity);

	}

	float light_received = ambient + diffuse + specular;
	return clamp(light_received, 0.0f, 1.0f);
}

/*
calculates the diffuse lighting at a hit point
returns a float in the range [0.0, 1.0] indicating the percentage of light received
*/
float Renderer::calculate_diffuse_lighting(const vec3& normal, const vec3& light_direction) {
	float diffuse = cos(angle(normal, light_direction));
	return std::max(0.0f, diffuse);
}

/*
calculates the specular reflection at a hit point
returns a float in the range [0.0, 1.0] indicating the percentage of light received 
*/
float Renderer::calculate_specular_reflections(const vec3& normal, const vec3& light_direction, const vec3& view_direction, float specularity) {
	vec3 r = reflect(light_direction, normal);
	float specular = dot(r, view_direction) / (magnitude(r) * magnitude(view_direction));
	return std::max(0.0f, std::powf(specular, specularity));
}

/*
creates a ppm image and calls trace_ray on every pixel in the scene
handles rendering options such as supersampling
*/
void Renderer::drop_ppm_image(std::ofstream& file, const Scene& scene) {
	Canvas canvas = scene.get_canvas();
	file.open(FileSystem::get_path("/img/image.ppm"));
	file << "P3\n" << canvas.width << ' ' << canvas.height << "\n255\n";
	for (int i = -canvas.height / 2; i < canvas.height / 2; i++) {
		for (int j = -canvas.width / 2; j < canvas.width / 2; j++) {
			vec3 color = BACKGROUND_COLOR;
			vec2 viewport_pos = canvas_to_viewport(canvas, scene.get_viewport(), j, i);
			vec3 view_direction = normalize(vec3(viewport_pos, scene.get_camera().get_direction().z));
			Ray view_ray(scene.get_camera().get_position(), view_direction);

			if (supersampling_levels > 0) {
				// calculate pixel dimensions for supersampling
				const float pixel_width = scene.get_viewport().width / scene.get_canvas().width;
				const float pixel_height = scene.get_viewport().height / scene.get_canvas().height;

				std::vector<Ray> rays = { view_ray };
				color = supersample(rays, scene, pixel_width / 4.0f, pixel_height / 4.0f, supersampling_levels);
			} 
			else {
				color = trace_ray(view_ray, scene, recursion_depth);
			}

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

/*
checks for ray intersections against all objects in a scene
returns a bool indicating if any object was hit by the ray
*/
bool Renderer::is_any_object_hit(const Ray& ray, const Scene& scene, const Shape* exclude) {
	for (const Sphere& sphere : scene.get_spheres()) {
		rays_cast++;

		if (&sphere == exclude)
			continue;
		
		if (intersects(ray, sphere)) {
			return true;
		}
	}

	return false;
}

/*
checks for ray intersections against all objects in a scene
hit data for the closest object hit is stored in hits
returns a bool indicating if any object was hit by the ray
*/
bool Renderer::raycast_scene(const Ray& ray, const Scene& scene, std::array<RaycastHit*, 2>& hits) {
	float least_distance = INFINITY;
	bool is_object_hit = false;
	for (const Sphere& sphere : scene.get_spheres()) {
		rays_cast++;
		std::array<RaycastHit*, 2> temp_hits = {};
		if (intersects(ray, sphere, temp_hits)) {
			is_object_hit = true;
			for (int i = 0; i < temp_hits.size(); i++) {
				float distance = magnitude(ray.get_origin() - temp_hits[i]->point);
				if (distance < least_distance) {
					least_distance = distance;
					hits = temp_hits;
				}
			}
		}
	}

	return is_object_hit;
}

/*
renders the scene provided
*/
void Renderer::render(const Scene& scene) {
	std::ofstream file;
	spdlog::stopwatch sw;
	drop_ppm_image(file, scene);
	spdlog::info("render(): {:.5}s", sw);
	spdlog::info("Total Rays Cast: {}", rays_cast);
}

/*
traces a ray agains the scene provided
returns a vec3 representing the color of a pixel after all intersection and lighting calculations
where each component is in the range [0.0, 1.0]
*/
vec3 Renderer::trace_ray(const Ray& ray, const Scene& scene, int recursion_depth) {
	std::array<RaycastHit*, 2> hits;
	vec3 local_color(BACKGROUND_COLOR);
	bool is_object_hit = raycast_scene(ray, scene, hits);

	if (is_object_hit) {
		float lighting = calculate_lighting(ray, scene, *hits[0]);
		local_color = lighting * hits[0]->object->get_material().color;
		return local_color;
	}
	else
		return BACKGROUND_COLOR;
}

/*
Recursively splits a ray into 4^levels rays equally spaced apart 
and traces each ray
returns a vec3 representing the averaged color of all of the rays
where each component is in the range [0.0, 1.0]
*/
vec3 Renderer::supersample(std::vector<Ray>& rays, const Scene& scene, float width, float height, int levels) {
	// average the color if done supersampling
	if (levels == 0) {
		vec3 color(0.0f);
		for (const Ray& ray : rays) {
			color += trace_ray(ray, scene, recursion_depth);
		}
		color /= rays.size();
		return color;
	}

	// offsets in each direction to supersample
	const std::array<vec3, 4> offset = {
		vec3(width, height),
		vec3(width, -height),
		vec3(-width, height),
		vec3(-width, -height)
	};

	// add supersample rays to new vector
	std::vector<Ray> rays_to_supersample;
	for (const Ray& ray : rays) {
		for (int i = 0; i < offset.size(); i++) {
			rays_to_supersample.push_back(
				Ray(ray.get_origin(), ray.get_direction() + offset[i])
			);
		}
	}

	// width and height need to be divided by 4
	// for each level of supersampling
	width /= 4;
	height /= 4;
	return supersample(rays_to_supersample, scene, width / 4.0f, height / 4.0f, --levels);
}
