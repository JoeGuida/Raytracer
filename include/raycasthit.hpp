#ifndef RAYTRACER_RAYCASTHIT_HPP
#define RAYTRACER_RAYCASTHIT_HPP

#include <utility>

class RaycastHit {
public:
	std::pair<float, float> points;

	RaycastHit() {}
	RaycastHit(const RaycastHit&) = default;
	RaycastHit(RaycastHit&&) = default;
	virtual ~RaycastHit() = default;
};

#endif