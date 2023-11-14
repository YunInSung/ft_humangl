#pragma once

#include <limits>

namespace glm{
	namespace detail
	{
		template <typename T, bool isFloat>
		struct compute_equal
		{
			static bool call(T a, T b)
			{
				return a == b;
			}
		};
	}//namespace detail
}//namespace glm
