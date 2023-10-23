#ifndef RAYTRACER_CANVAS_HPP
#define RAYTRACER_CANVAS_HPP

class Canvas {
private:
	int width;
	int height;

public:
	int get_width() const { return width; }
	int get_height() const { return height; }

	Canvas(int width, int height) : width(width), height(height) {}
	Canvas(const Canvas&) = default;
	Canvas(Canvas&&) = default;
	virtual ~Canvas() = default;
};

#endif