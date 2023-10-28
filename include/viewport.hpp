#ifndef RAYTRACER_VIEWPORT_HPP
#define RAYTRACER_VIEWPORT_HPP

#include "canvas.hpp"
#include "vectors.hpp"

class Viewport {
public:
	float width;
	float height;

	Viewport(float width, float height) : width(width), height(height) {}
	Viewport(const Viewport&) = default;
	Viewport(Viewport&&) = default;
	virtual ~Viewport() = default;
};

vec2 canvas_to_viewport(const Canvas& canvas, const Viewport& viewport, int canvas_x, int canvas_y);

#endif