#pragma once
#include "mat4x4.hpp"

namespace glm {
	struct qua {
		typedef qua type;
		typedef float value_type;
		float x, y, z, w;

		float & operator[](int i);
		float const& operator[](int i) const;

		qua();
		qua(qua const& q);

		// -- Explicit basic constructors --
		qua(float s, vec3 const& v);
		qua(float w, float x, float y, float z);
	};
};