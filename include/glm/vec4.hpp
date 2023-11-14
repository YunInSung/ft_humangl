#pragma once

#include "vec3.hpp"

namespace glm {
	struct vec4
	{
		float x, y, z, w;

		float & operator[](int i);
		float const& operator[](int i) const;

		vec4();
		vec4(vec4 const& v);
		vec4(float scalar);
		vec4(float x, float y, float z, float w);

		vec4(vec2 const& _xy, float _z, float _w);
		vec4(float _x, vec2 const& _yz, float _w);
		vec4(float _x, float _y, vec2 const& _zw);
		vec4(vec3 const& _xyz, float _w);
		vec4(float _x, vec3 const& _yzw);
		vec4(vec2 const& _xy, vec2 const& _zw);

		vec4& operator=(vec4 const& v);
		vec4& operator+=(float scalar);
		vec4& operator+=(vec4 const& v);
		vec4& operator-=(float scalar);
		vec4& operator-=(vec4 const& v);
		vec4& operator*=(float scalar);
		vec4& operator*=(vec4 const& v);
		vec4& operator/=(float scalar);
		vec4& operator/=(vec4 const& v);

		vec4 & operator++();
		vec4 & operator--();
		vec4 operator++(int);
		vec4 operator--(int);
	};

	vec4 operator+(vec4 const& v);
	vec4 operator-(vec4 const& v);
	vec4 operator+(vec4 const& v, float const & scalar);
	vec4 operator+(float scalar, vec4 const& v);
	vec4 operator+(vec4 const& v1, vec4 const& v2);
	vec4 operator-(vec4 const& v, float const & scalar);
	vec4 operator-(float scalar, vec4 const& v);
	vec4 operator-(vec4 const& v1, vec4 const& v2);
	vec4 operator*(vec4 const& v, float const & scalar);
	vec4 operator*(float scalar, vec4 const& v);
	vec4 operator*(vec4 const& v1, vec4 const& v2);
	vec4 operator/(vec4 const& v, float const & scalar);
	vec4 operator/(float scalar, vec4 const& v);
	vec4 operator/(vec4 const& v1, vec4 const& v2);
	bool operator==(vec4 const& v1, vec4 const& v2);
	bool operator!=(vec4 const& v1, vec4 const& v2);
}