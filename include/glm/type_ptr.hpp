#pragma once

#include "mat2x2.hpp"
#include "mat3x3.hpp"
#include "mat4x4.hpp"

namespace glm {
	float const* value_ptr(vec2 const& v);
	float* value_ptr(vec2& v);
	float const * value_ptr(vec3 const& v);
	float* value_ptr(vec3& v);
	float const* value_ptr(vec4 const& v);
	float* value_ptr(vec4& v);
	float const* value_ptr(mat2 const& m);
	float* value_ptr(mat2& m);
	float const* value_ptr(mat3 const& m);
	float* value_ptr(mat3& m);
	float const* value_ptr(mat4 const& m);
	float* value_ptr(mat4& m);
};