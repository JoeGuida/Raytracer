#include "viewport.hpp"

vec2 canvas_to_viewport(const Canvas& canvas, const Viewport& viewport, int canvas_x, int canvas_y) {
	float width = viewport.width / canvas.width;
	float height = viewport.height / canvas.height;
	float viewport_x = width * canvas.width / 2.0f + canvas_x;
	float viewport_y = height * canvas.height / 2.0f + canvas_y;
	return vec2(viewport_x, viewport_y);
}