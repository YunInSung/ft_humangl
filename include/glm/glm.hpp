#pragma once

#include "mat4x4.hpp"
#include "mat3x3.hpp"
#include "mat2x2.hpp"
#include "type_ptr.hpp"
#include <cmath>

#include <iostream>

namespace glm {
	float pi();
	float determinant(mat2 const& m);
	float determinant(mat3 const& m);
	float determinant(mat4 const& m);
	mat2 transpose(mat2 const& m);
	mat3 transpose(mat3 const& m);
	mat4 transpose(mat4 const& m);
	mat2 inverse(mat2 const& m);
	mat3 inverse(mat3 const& m);
	mat4 inverse(mat4 const& m);

	float radians(float degrees);
	float length(vec2 const& v);
	float length(vec3 const& v);
	float length(vec4 const& v);
	float distance(vec2 const& p0, vec2 const& p1);
	float distance(vec3 const& p0, vec3 const& p1);
	float distance(vec4 const& p0, vec4 const& p1);
	vec2 normalize(vec2 v);
	vec3 normalize(vec3 v);
	vec4 normalize(vec4 v);

	mat4 translate(mat4 const& m, vec3 const& v);
	mat4 rotate(mat4 const& m, float angle, vec3 const& v);
	mat4 perspective(float fovy, float aspect, float zNear, float zFar);
	vec3 cross(vec3 const& a, vec3 const& b);
	mat4 lookAt(vec3 const& eye, vec3 const& center, vec3 const& up);
	mat4 scale(mat4 const& m, vec3 const& v);

	float dot(vec2 const& x, vec2 const& y);
	float dot(vec3 const& x, vec3 const& y);
	float dot(vec4 const& x, vec4 const& y);

	float lerp(float x, float y, float a);
	vec2 lerp(const vec2& x, const vec2& y, float a);
	vec3 lerp(const vec3& x, const vec3& y, float a);
	vec4 lerp(const vec4& x, const vec4& y, float a);

	vec3 slerp(const vec3& x, const vec3& y, float a);
};