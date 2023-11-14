#include "type_ptr.hpp"

namespace glm {
	float const* value_ptr(vec2 const& v)
	{
		return &(v.x);
	}

	float* value_ptr(vec2& v)
	{
		return &(v.x);
	}

	float const * value_ptr(vec3 const& v)
	{
		return &(v.x);
	}

	float* value_ptr(vec3& v)
	{
		return &(v.x);
	}

	float const* value_ptr(vec4 const& v)
	{
		return &(v.x);
	}

	float* value_ptr(vec4& v)
	{
		return &(v.x);
	}

	float const* value_ptr(mat2 const& m)
	{
		return &(m[0].x);
	}

	float* value_ptr(mat2& m)
	{
		return &(m[0].x);
	}

	float const* value_ptr(mat3 const& m)
	{
		return &(m[0].x);
	}

	float* value_ptr(mat3& m)
	{
		return &(m[0].x);
	}

	float const* value_ptr(mat4 const& m)
	{
		return &(m[0].x);
	}

	float* value_ptr(mat4& m)
	{
		return &(m[0].x);
	}
};