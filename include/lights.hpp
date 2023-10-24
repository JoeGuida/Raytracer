#ifndef RAYTRACER_LIGHTS_HPP
#define RAYTRACER_LIGHTS_HPP

#include <array>

#include "vectors.hpp"

class Light {
public:
	virtual float get_intensity() const = 0;
};

class AmbientLight : public Light {
private:
	float intensity;

public:
	float get_intensity() const override { return intensity; }

	AmbientLight(float intensity) : intensity(intensity) {}
	AmbientLight(const AmbientLight&) = default;
	AmbientLight(AmbientLight&&) = default;
	virtual ~AmbientLight() = default;
};

class DirectionalLight : public Light {
private:
	float intensity;
	vec3 direction;

public:
	float get_intensity() const override { return intensity; }
	vec3 get_direction() const { return direction; }

	DirectionalLight(float intensity, const vec3& direction) : 
		intensity(intensity), 
		direction(normalize(direction)) {}
	DirectionalLight(const DirectionalLight&) = default;
	DirectionalLight(DirectionalLight&&) = default;
	virtual ~DirectionalLight() = default;
};

class PointLight : public Light {
private:
	float intensity;
	vec3 position;
	float range;

public:
	float get_attenuation(float distance, float constant = 1.0f, float linear = 0.14f, float quadratic = 0.07f);
	float get_intensity() const override { return intensity; }
	vec3 get_position() const { return position; }
	float get_range() const { return range; }

	PointLight(float intensity, const vec3& position, float range) : 
		intensity(intensity), 
		position(position),
		range(range) {}
	PointLight(const PointLight&) = default;
	PointLight(PointLight&&) = default;
	virtual ~PointLight() = default;
};
#endif