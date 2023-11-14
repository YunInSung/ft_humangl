#include "vec3.hpp"
#include <cstdlib>
#include "compute_vector_relational.hpp"

namespace glm
{
	vec3::vec3() : x(0), y(0), z(0) {}

	vec3::vec3(vec3 const& v) : x(v.x), y(v.y), z(v.z) {}

	vec3::vec3(float scalar) : x(scalar), y(scalar), z(scalar) {}

	vec3::vec3(float a, float b, float c): x(a), y(b), z(c) {}

	vec3::vec3(vec2 _xy, float z) : x(_xy.x), y(_xy.y), z(z) {}

	vec3::vec3(float x, vec2 _yz) : x(x), y(_yz.x), z(_yz.y) {}


	float& vec3::vec3::operator[](int i)
	{
		if (!(i >= 0 && i < 3))
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
				case 2:
			return z;
		}
	}

	float const& vec3::vec3::operator[](int i) const
	{
		if (!(i >= 0 && i < 3))
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
			case 2:
				return z;
		}
	}

	vec3& vec3::operator=(vec3 const& v)
	{
		this->x = (v.x);
		this->y = (v.y);
		this->z = (v.z);
		return *this;
	}

	vec3& vec3::operator+=(float scalar)
	{
		this->x += (scalar);
		this->y += (scalar);
		this->z += (scalar);
		return *this;
	}

	vec3& vec3::operator+=(vec3 const& v)
	{
		this->x += (v.x);
		this->y += (v.y);
		this->z += (v.z);
		return *this;
	}

	vec3& vec3::operator-=(float scalar)
	{
		this->x -= (scalar);
		this->y -= (scalar);
		this->z -= (scalar);
		return *this;
	}

	vec3& vec3::operator-=(vec3 const& v)
	{
		this->x -= (v.x);
		this->y -= (v.y);
		this->z -= (v.z);
		return *this;
	}

	vec3& vec3::operator*=(float scalar)
	{
		this->x *= (scalar);
		this->y *= (scalar);
		this->z *= (scalar);
		return *this;
	}

	vec3& vec3::operator*=(vec3 const& v)
	{
		this->x *= (v.x);
		this->y *= (v.y);
		this->z *= (v.z);
		return *this;
	}

	vec3& vec3::operator/=(float v)
	{
		this->x /= (v);
		this->y /= (v);
		this->z /= (v);
		return *this;
	}

	vec3& vec3::operator/=(vec3 const& v)
	{
		this->x /= (v.x);
		this->y /= (v.y);
		this->z /= (v.z);
		return *this;
	}

	vec3& vec3::operator++()
	{
		++this->x;
		++this->y;
		++this->z;
		return *this;
	}

	vec3& vec3::operator--()
	{
		--this->x;
		--this->y;
		--this->z;
		return *this;
	}

	vec3 vec3::operator++(int)
	{
		vec3 Result(*this);
		++*this;
		return Result;
	}

	vec3 vec3::operator--(int)
	{
		vec3 Result(*this);
		--*this;
		return Result;
	}

	vec3 operator+(vec3 const& v)
	{
		return v;
	}

	vec3 operator-(vec3 const& v)
	{
		return vec3(
			-v.x,
			-v.y,
			-v.z);
	}

	vec3 operator+(vec3 const& v, float scalar)
	{
		return vec3(
			v.x + scalar,
			v.y + scalar,
			v.z + scalar);
	}

	vec3 operator+(float scalar, vec3 const& v)
	{
		return vec3(
			scalar + v.x,
			scalar + v.y,
			scalar + v.z);
	}

	vec3 operator+(vec3 const& v1, vec3 const& v2)
	{
		return vec3(
			v1.x + v2.x,
			v1.y + v2.y,
			v1.z + v2.z);
	}

	vec3 operator-(vec3 const& v, float scalar)
	{
		return vec3(
			v.x - scalar,
			v.y - scalar,
			v.z - scalar);
	}

	vec3 operator-(float scalar, vec3 const& v)
	{
		return vec3(
			scalar - v.x,
			scalar - v.y,
			scalar - v.z);
	}

	vec3 operator-(vec3 const& v1, vec3 const& v2)
	{
		return vec3(
			v1.x - v2.x,
			v1.y - v2.y,
			v1.z - v2.z);
	}

	vec3 operator*(vec3 const& v, float scalar)
	{
		return vec3(
			v.x * scalar,
			v.y * scalar,
			v.z * scalar);
	}

	vec3 operator*(float scalar, vec3 const& v)
	{
		return vec3(
			scalar * v.x,
			scalar * v.y,
			scalar * v.z);
	}

	vec3 operator*(vec3 const& v1, vec3 const& v2)
	{
		return vec3(
			v1.x * v2.x,
			v1.y * v2.y,
			v1.z * v2.z);
	}

	vec3 operator/(vec3 const& v, float scalar)
	{
		return vec3(
			v.x / scalar,
			v.y / scalar,
			v.z / scalar);
	}

	vec3 operator/(float scalar, vec3 const& v)
	{
		return vec3(
			scalar / v.x,
			scalar / v.y,
			scalar / v.z);
	}

	vec3 operator/(vec3 const& v1, vec3 const& v2)
	{
		return vec3(
			v1.x / v2.x,
			v1.y / v2.y,
			v1.z / v2.z);
	}

	bool operator==(vec3 const& v1, vec3 const& v2)
	{
		return
			detail::compute_equal<float, std::numeric_limits<float>::is_iec559>::call(v1.x, v2.x) &&
			detail::compute_equal<float, std::numeric_limits<float>::is_iec559>::call(v1.y, v2.y) &&
			detail::compute_equal<float, std::numeric_limits<float>::is_iec559>::call(v1.z, v2.z);
	}

	bool operator!=(vec3 const& v1, vec3 const& v2)
	{
		return !(v1 == v2);
	}
}