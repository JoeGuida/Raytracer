#include "lights.hpp"

float PointLight::get_attenuation(float distance, float constant, float linear, float quadratic) {
	return 1.0f / (constant + linear * distance + quadratic * std::powf(distance, 2.0f));
}