#include "vectors.hpp"

// ----------------------------------------------------------------------------
// Vector2
// ----------------------------------------------------------------------------

vec2& vec2::operator=(const vec2& v) {
	x = v.x;
	y = v.y;
	return *this;
}

void vec2::operator+=(float s) {
	x += s;
	y += s;
}

void vec2::operator+=(const vec2& v) {
	x += v.x;
	y += v.y;
}

void vec2::operator-=(float s) {
	x -= s;
	y -= s;
}

void vec2::operator-=(const vec2& v) {
	x -= v.x;
	y -= v.y;
}

void vec2::operator*=(float s) {
	x *= s;
	y *= s;
}

void vec2::operator*=(const vec2& v) {
	x *= v.x;
	y *= v.y;
}

void vec2::operator/=(float s) {
	s = 1.0f / s;
	x *= s;
	y *= s;
}

std::ostream& operator<<(std::ostream& os, vec2& v) {
	os << '(' << v.x << ' ' << v.y << ')' << std::endl;
	return os;
}

vec2 operator+(const vec2& v, float s) {
	return { v.x + s, v.y + s };
}

vec2 operator+(const vec2& a, const vec2& b) {
	return { a.x + b.x, a.y + b.y };
}

vec2 operator-(const vec2& v, float s) {
	return { v.x - s, v.y - s };
}

vec2 operator-(const vec2& a, const vec2& b) {
	return { a.x - b.x, a.y - b.y };
}

vec2 operator-(const vec2& v) {
	return { -v.x, -v.y };
}

vec2 operator*(const vec2& v, float s) {
	return { v.x * s, v.y * s };
}

vec2 operator*(const vec2& a, const vec2& b) {
	return { a.x * b.x, a.y * b.y };
}

vec2 operator/(const vec2& v, float s) {
	s = 1.0f / s;
	return v * s;
}

bool operator==(const vec2& a, const vec2& b) {
	return compare_float(a.x, b.x) && compare_float(a.y, b.y);
}

bool operator!=(const vec2& a, const vec2& b) {
	return !(a == b);
}

// ----------------------------------------------------------------------------
// Vector3
// ----------------------------------------------------------------------------

vec3& vec3::operator=(const vec3& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

void vec3::operator+=(float s) {
	x += s;
	y += s;
	z += s;
}

void vec3::operator+=(const vec3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
}

void vec3::operator-=(float s) {
	x -= s;
	y -= s;
	z -= s;
}

void vec3::operator-=(const vec3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

void vec3::operator*=(float s) {
	x *= s;
	y *= s;
	z *= s;
}

void vec3::operator*=(const vec3& v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
}

void vec3::operator/=(float s) {
	s = 1.0f / s;
	x *= s;
	y *= s;
	z *= s;
}

std::ostream& operator<<(std::ostream& os, vec3& v) {
	os << '(' << v.x << ' ' << v.y << ' ' << v.z << ')' << std::endl;
	return os;
}

vec3 operator+(const vec3& v, float s) {
	return { v.x + s, v.y + s, v.z + s };
}

vec3 operator+(const vec3& a, const vec3& b) {
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

vec3 operator-(const vec3& v, float s) {
	return { v.x - s, v.y - s, v.z - s };
}

vec3 operator-(const vec3& a, const vec3& b) {
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}

vec3 operator-(const vec3& v) {
	return { -v.x, -v.y, -v.z };
}

vec3 operator*(const vec3& v, float s) {
	return { v.x * s, v.y * s, v.z * s };
}

vec3 operator*(const vec3& a, const vec3& b) {
	return { a.x * b.x, a.y * b.y, a.z * b.z };
}

vec3 operator/(const vec3& v, float s) {
	s = 1.0f / s;
	return v * s;
}

bool operator==(const vec3& a, const vec3& b) {
	return compare_float(a.x, b.x) && compare_float(a.y, b.y) && compare_float(a.z, b.z);
}

bool operator!=(const vec3& a, const vec3& b) {
	return !(a == b);
}

float angle(const vec3& a, const vec3& b) {
	return acosf(dot(a, b) / (magnitude(a) * magnitude(b)));
}

vec3 cross(const vec3& a, const vec3& b) {
	float x = (a.y * b.z - a.z * b.y);
	float y = (a.z * b.x - a.x * b.z);
	float z = (a.x * b.y - a.y * b.x);
	return { x, y, z };
}

float dot(const vec3& a, const vec3& b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

float magnitude(const vec3& v) {
	return sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

vec3 normalize(const vec3& v) {
	return v / magnitude(v);
}

vec3 perpendicular(const vec3& a, const vec3& b) {
	return a - project(a, b);
}

vec3 project(const vec3& a, const vec3& b) {
	return b * dot(a, b) / dot(b, b);
}

vec3 reflect(const vec3& v, const vec3& n) {
	return v - (2 * dot(v, n) * n);
}

// ----------------------------------------------------------------------------
// Vector4
// ----------------------------------------------------------------------------

vec4& vec4::operator=(const vec4& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}

void vec4::operator+=(float s) {
	x += s;
	y += s;
	z += s;
	w += s;
}

void vec4::operator+=(const vec4& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
}

void vec4::operator-=(float s) {
	x -= s;
	y -= s;
	z -= s;
	w -= s;
}

void vec4::operator-=(const vec4& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
}

void vec4::operator*=(float s) {
	x *= s;
	y *= s;
	z *= s;
	w *= s;
}

void vec4::operator*=(const vec4& v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;
}

void vec4::operator/=(float s) {
	s = 1.0f / s;
	x *= s;
	y *= s;
	z *= s;
	w *= s;
}

std::ostream& operator<<(std::ostream& os, vec4& v) {
	os << '(' << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w << ')' << std::endl;
	return os;
}

vec4 operator+(const vec4& v, float s) {
	return { v.x + s, v.y + s, v.z + s, v.w + s };
}

vec4 operator+(const vec4& a, const vec4& b) {
	return { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
}

vec4 operator-(const vec4& v, float s) {
	return { v.x - s, v.y - s, v.z - s, v.w - s };
}

vec4 operator-(const vec4& a, const vec4& b) {
	return { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
}

vec4 operator-(const vec4& v) {
	return { -v.x, -v.y, -v.z, -v.w };
}

vec4 operator*(const vec4& v, float s) {
	return { v.x * s, v.y * s, v.z * s, v.w * s };
}

vec4 operator*(const vec4& a, const vec4& b) {
	return { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
}

vec4 operator/(const vec4& v, float s) {
	s = 1.0f / s;
	return v * s;
}

bool operator==(const vec4& a, const vec4& b) {
	return compare_float(a.x, b.x) && compare_float(a.y, b.y) &&
		   compare_float(a.z, b.z) && compare_float(a.w, b.w);
}

bool operator!=(const vec4& a, const vec4& b) {
	return !(a == b);
}
