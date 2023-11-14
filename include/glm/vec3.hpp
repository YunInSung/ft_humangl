#pragma once

#include "vec2.hpp"

namespace glm {
	struct vec3
	{
		float x, y, z;

		float & operator[](int i);
		float const& operator[](int i) const;
		vec3();
		vec3(vec3 const& v);
		vec3(float scalar);
		vec3(float a, float b, float c);
		vec3(vec2 _xy, float z);
		vec3(float x, vec2 _yz);

		vec3& operator=(vec3 const& v);
		vec3& operator+=(vec3 const& v);
		vec3& operator+=(float scalar);
		vec3& operator-=(float scalar);
		vec3& operator-=(vec3 const& v);
		vec3& operator*=(float scalar);
		vec3& operator*=(vec3 const& v);
		vec3& operator/=(float scalar);
		vec3& operator/=(vec3 const& v);

		vec3 & operator++();
		vec3 & operator--();
		vec3 operator++(int);
		vec3 operator--(int);

	};
	vec3 operator+(vec3 const& v);
	vec3 operator-(vec3 const& v);

	vec3 operator+(vec3 const& v, float scalar);
	vec3 operator+(float scalar, vec3 const& v);
	vec3 operator+(vec3 const& v1, vec3 const& v2);
	vec3 operator-(vec3 const& v, float scalar);
	vec3 operator-(float scalar, vec3 const& v);
	vec3 operator-(vec3 const& v1, vec3 const& v2);
	vec3 operator*(vec3 const& v, float scalar);
	vec3 operator*(float scalar, vec3 const& v);
	vec3 operator*(vec3 const& v1, vec3 const& v2);
	vec3 operator/(vec3 const& v, float scalar);
	vec3 operator/(float scalar, vec3 const& v);
	vec3 operator/(vec3 const& v1, vec3 const& v2);
	bool operator==(vec3 const& v1, vec3 const& v2);
	bool operator!=(vec3 const& v1, vec3 const& v2);
}