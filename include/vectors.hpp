#ifndef RAYTRACER_VECTORS_HPP
#define RAYTRACER_VECTORS_HPP

#include <ostream>

#include "helpers.hpp"

class vec2 {
public:
	float x;
	float y;

	vec2(float s) : x(s), y(s) {}
	vec2(float x, float y) : x(x), y(y) {}
	vec2(const vec2&) = default;
	vec2(vec2&&) = default;
	virtual ~vec2() = default;

	vec2& operator=(const vec2& v);
	void operator+=(float s);
	void operator+=(const vec2& v);
	void operator-=(float s);
	void operator-=(const vec2& v);
	void operator*=(float s);
	void operator*=(const vec2& v);
	void operator/=(float s);
};

class vec3 {
public:
	float x;
	float y;
	float z;

	vec3(float s) : x(s), y(s), z(s) {}
	vec3(float x, float y, float z) : x(x), y(y), z(z) {}
	vec3(const vec2& v, float z) : x(v.x), y(v.y), z(z) {}
	vec3(const vec3&) = default;
	vec3(vec3&&) = default;
	virtual ~vec3() = default;

	vec3& operator=(const vec3& v);
	void operator+=(float s);
	void operator+=(const vec3& v);
	void operator-=(float s);
	void operator-=(const vec3& v);
	void operator*=(float s);
	void operator*=(const vec3& v);
	void operator/=(float s);
};

class vec4 {
public:
	float x;
	float y;
	float z;
	float w;

	vec4(float s) : x(s), y(s), z(s), w(s) {}
	vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	vec4(const vec3& v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}
	vec4(const vec4&) = default;
	vec4(vec4&&) = default;
	virtual ~vec4() = default;

	vec4& operator=(const vec4& v);
	void operator+=(float s);
	void operator+=(const vec4& v);
	void operator-=(float s);
	void operator-=(const vec4& v);
	void operator*=(float s);
	void operator*=(const vec4& v);
	void operator/=(float s);
};

std::ostream& operator<<(std::ostream& os, vec2& v);
std::ostream& operator<<(std::ostream& os, vec3& v);
std::ostream& operator<<(std::ostream& os, vec4& v);
vec2 operator+(const vec2& v, float s);
vec2 operator+(const vec2& a, const vec2& b);
vec3 operator+(const vec3& v, float s);
vec3 operator+(const vec3& a, const vec3& b);
vec4 operator+(const vec4& v, float s);
vec4 operator+(const vec4& a, const vec4& b);
vec2 operator-(const vec2& v, float s);
vec2 operator-(const vec2& a, const vec2& b);
vec2 operator-(const vec2& v);
vec3 operator-(const vec3& v, float s);
vec3 operator-(const vec3& a, const vec3& b);
vec3 operator-(const vec3& v);
vec4 operator-(const vec4& v, float s);
vec4 operator-(const vec4& a, const vec4& b);
vec4 operator-(const vec4& v);
vec2 operator*(const vec2& v, float s);
vec2 operator*(const vec2& a, const vec2& b);
vec3 operator*(const vec3& v, float s);
vec3 operator*(const vec3& a, const vec3& b);
vec4 operator*(const vec4& v, float s);
vec4 operator*(const vec4& a, const vec4& b);
vec2 operator/(const vec2& v, float s);
vec3 operator/(const vec3& v, float s);
vec4 operator/(const vec4& v, float s);
bool operator==(const vec2& a, const vec2& b);
bool operator==(const vec3& a, const vec3& b);
bool operator==(const vec4& a, const vec4& b);
bool operator!=(const vec2& a, const vec2& b);
bool operator!=(const vec3& a, const vec3& b);
bool operator!=(const vec4& a, const vec4& b);
float angle(const vec3& a, const vec3& b);
vec3 cross(const vec3& a, const vec3& b);
float dot(const vec3& a, const vec3& b);
float magnitude(const vec3& v);
vec3 normalize(const vec3& v);
vec3 perpendicular(const vec3& a, const vec3& b);
vec3 project(const vec3& a, const vec3& b);
vec3 reflect(const vec3& a, const vec3& b);

#endif