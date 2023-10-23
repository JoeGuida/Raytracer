#include "viewport.hpp"

vec2 canvas_to_viewport(const Canvas& canvas, const Viewport& viewport, int canvas_x, int canvas_y) {
	float width = viewport.get_width() / canvas.get_width();
	float height = viewport.get_height() / canvas.get_height();
	float viewport_x = width * canvas.get_width() / 2.0f + canvas_x;
	float viewport_y = height * canvas.get_height() / 2.0f + canvas_y;
	return vec2(viewport_x, viewport_y);
}