#pragma once

namespace glm {
	struct vec2
	{
		float x, y;

		float & operator[](int i);
		float const& operator[](int i) const;
		vec2();
		vec2(vec2 const& v);
		vec2(float scalar);
		vec2(float a, float b);

		vec2 & operator=(vec2 const& v);
		vec2 & operator+=(float scalar);
		vec2 & operator+=(vec2 const& v);
		vec2 & operator-=(float scalar);
		vec2 & operator-=(vec2 const& v);
		vec2 & operator*=(float scalar);
		vec2 & operator*=(vec2 const& v);
		vec2 & operator/=(float scalar);
		vec2 & operator/=(vec2 const& v);

		vec2 & operator++();
		vec2 & operator--();
		vec2 operator++(int);
		vec2 operator--(int);
	};

	vec2 operator+(vec2 const& v);
	vec2 operator-(vec2 const& v);
	vec2 operator+(vec2 const& v, float scalar);
	vec2 operator+(float scalar, vec2 const& v);
	vec2 operator+(vec2 const& v1, vec2 const& v2);
	vec2 operator-(vec2 const& v, float scalar);
	vec2 operator-(float scalar, vec2 const& v);
	vec2 operator-(vec2 const& v1, vec2 const& v2);
	vec2 operator*(vec2 const& v, float scalar);
	vec2 operator*(float scalar, vec2 const& v);
	vec2 operator*(vec2 const& v1, vec2 const& v2);
	vec2 operator/(vec2 const& v, float scalar);
	vec2 operator/(float scalar, vec2 const& v);
	vec2 operator/(vec2 const& v1, vec2 const& v2);
	bool operator==(vec2 const& v1, vec2 const& v2);
	bool operator!=(vec2 const& v1, vec2 const& v2);
}