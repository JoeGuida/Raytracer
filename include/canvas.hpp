#ifndef RAYTRACER_CANVAS_HPP
#define RAYTRACER_CANVAS_HPP

class Canvas {
public:
	int width;
	int height;

	Canvas(int width, int height) : width(width), height(height) {}
	Canvas(const Canvas&) = default;
	Canvas(Canvas&&) = default;
	virtual ~Canvas() = default;
};

#endif