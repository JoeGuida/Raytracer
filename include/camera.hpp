#ifndef RAYTRACER_CAMERA_HPP
#define RAYTRACER_CAMERA_HPP

#include "vectors.hpp"

class Camera {
private:
	vec3 position;
	vec3 direction;

public:
	vec3 get_position() const { return position; }
	vec3 get_direction() const { return direction; }

	Camera(const vec3& position, const vec3& direction) : position(position), direction(direction) {}
};

#endif()