#include "vec2.hpp"
#include <cstdlib>
#include "compute_vector_relational.hpp"

namespace glm {
	vec2::vec2(): x(0), y(0) {}

	vec2::vec2(vec2 const& v): x(v.x), y(v.y) {}

	vec2::vec2(float scalar): x(scalar), y(scalar) {}

	vec2::vec2(float _x, float _y): x(_x), y(_y) {}

	float & vec2::operator[](int i)
	{
		if (!(i >= 0 && i < 2))
		{
			std::exit(-1);
		}
		switch(i)
		{
			default:
			case 0:
				return x;
			case 1:
				return y;
		}
	}

	float const& vec2::operator[](int i) const
	{
		if (!(i >= 0 && i < 2))
		{
			std::exit(-1);
		}
		switch(i)
		{
			default:
			case 0:
				return x;
			case 1:
				return y;
		}
	}

	vec2& vec2::operator=(vec2 const& v)
	{
		this->x = (v.x);
		this->y = (v.y);
		return *this;
	}

	vec2 & vec2::operator+=(float scalar)
	{
		this->x += (scalar);
		this->y += (scalar);
		return *this;
	}

	vec2 & vec2::operator+=(vec2 const& v)
	{
		this->x += (v.x);
		this->y += (v.y);
		return *this;
	}

	vec2 & vec2::operator-=(float scalar)
	{
		this->x -= (scalar);
		this->y -= (scalar);
		return *this;
	}

	vec2 & vec2::operator-=(vec2 const& v)
	{
		this->x -= (v.x);
		this->y -= (v.y);
		return *this;
	}

	vec2 & vec2::operator*=(float scalar)
	{
		this->x *= (scalar);
		this->y *= (scalar);
		return *this;
	}

	vec2& vec2::operator*=(vec2 const& v)
	{
		this->x *= (v.x);
		this->y *= (v.y);
		return *this;
	}

	vec2 & vec2::operator/=(float scalar)
	{
		this->x /= (scalar);
		this->y /= (scalar);
		return *this;
	}

	vec2 & vec2::operator/=(vec2 const& v)
	{
		this->x /= (v.x);
		this->y /= (v.y);
		return *this;
	}

	vec2 & vec2::operator++()
	{
		++this->x;
		++this->y;
		return *this;
	}

	vec2 & vec2::operator--()
	{
		--this->x;
		--this->y;
		return *this;
	}

	vec2 vec2::operator++(int)
	{
		vec2 Result(*this);
		++*this;
		return Result;
	}

	vec2 vec2::operator--(int)
	{
		vec2 Result(*this);
		--*this;
		return Result;
	}

	vec2 operator+(vec2 const& v)
	{
		return v;
	}

	vec2 operator-(vec2 const& v)
	{
		return vec2(
			-v.x,
			-v.y);
	}

	vec2 operator+(vec2 const& v, float scalar)
	{
		return vec2(
			v.x + scalar,
			v.y + scalar);
	}


	vec2 operator+(float scalar, vec2 const& v)
	{
		return vec2(
			scalar + v.x,
			scalar + v.y);
	}

	vec2 operator+(vec2 const& v1, vec2 const& v2)
	{
		return vec2(
			v1.x + v2.x,
			v1.y + v2.y);
	}

	vec2 operator-(vec2 const& v, float scalar)
	{
		return vec2(
			v.x - scalar,
			v.y - scalar);
	}

	vec2 operator-(float scalar, vec2 const& v)
	{
		return vec2(
			scalar - v.x,
			scalar - v.y);
	}

	vec2 operator-(vec2 const& v1, vec2 const& v2)
	{
		return vec2(
			v1.x - v2.x,
			v1.y - v2.y);
	}

	vec2 operator*(vec2 const& v, float scalar)
	{
		return vec2(
			v.x * scalar,
			v.y * scalar);
	}

	vec2 operator*(float scalar, vec2 const& v)
	{
		return vec2(
			scalar * v.x,
			scalar * v.y);
	}

	vec2 operator*(vec2 const& v1, vec2 const& v2)
	{
		return vec2(
			v1.x * v2.x,
			v1.y * v2.y);
	}

	vec2 operator/(vec2 const& v, float scalar)
	{
		return vec2(
			v.x / scalar,
			v.y / scalar);
	}

	vec2 operator/(float scalar, vec2 const& v)
	{
		return vec2(
			scalar / v.x,
			scalar / v.y);
	}

	vec2 operator/(vec2 const& v1, vec2 const& v2)
	{
		return vec2(
			v1.x / v2.x,
			v1.y / v2.y);
	}

	bool operator==(vec2 const& v1, vec2 const& v2)
	{
		return
			detail::compute_equal<float, std::numeric_limits<float>::is_iec559>::call(v1.x, v2.x) &&
			detail::compute_equal<float, std::numeric_limits<float>::is_iec559>::call(v1.y, v2.y);
	}

	bool operator!=(vec2 const& v1, vec2 const& v2)
	{
		return !(v1 == v2);
	}

};