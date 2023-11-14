#include "vec4.hpp"
#include <cstdlib>
#include "compute_vector_relational.hpp"

namespace glm {
	vec4::vec4(): x(0), y(0), z(0), w(0) {}

	vec4::vec4(vec4 const& v): x(v.x), y(v.y), z(v.z), w(v.w) {}

	vec4::vec4(float scalar): x(scalar), y(scalar), z(scalar), w(scalar) {}

	vec4::vec4(float _x, float _y, float _z, float _w): x(_x), y(_y), z(_z), w(_w) {}

	vec4::vec4(vec2 const& _xy, float _z, float _w)
		: x((_xy.x))
		, y((_xy.y))
		, z((_z))
		, w((_w))
	{}

	vec4::vec4(float _x, vec2 const& _yz, float _w)
		: x((_x))
		, y((_yz.x))
		, z((_yz.y))
		, w((_w))
	{}

	vec4::vec4(float _x, float _y, vec2 const& _zw)
		: x((_x))
		, y((_y))
		, z((_zw.x))
		, w((_zw.y))
	{}

	vec4::vec4(vec3 const& _xyz, float _w)
		: x((_xyz.x))
		, y((_xyz.y))
		, z((_xyz.z))
		, w((_w))
	{}

	vec4::vec4(float _x, vec3 const& _yzw)
		: x((_x))
		, y((_yzw.x))
		, z((_yzw.y))
		, w((_yzw.z))
	{}

	vec4::vec4(vec2 const& _xy, vec2 const& _zw)
		: x((_xy.x))
		, y((_xy.y))
		, z((_zw.x))
		, w((_zw.y))
	{}

	float& vec4::operator[](int i)
	{
		if (!(i >= 0 && i < 4))
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
		case 3:
			return w;
		}
	}

	float const& vec4::operator[](int i) const
	{
		if (!(i >= 0 && i < 4))
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
		case 3:
			return w;
		}
	}

	vec4& vec4::operator=(vec4 const& v)
	{
		this->x = (v.x);
		this->y = (v.y);
		this->z = (v.z);
		this->w = (v.w);
		return *this;
	}

	vec4& vec4::operator+=(float scalar)
	{
		this->x += scalar;
		this->y += scalar;
		this->z += scalar;
		this->w += scalar;
		return *this;
	}

	vec4& vec4::operator+=(vec4 const& v)
	{
		this->x += (v.x);
		this->y += (v.y);
		this->z += (v.z);
		this->w += (v.w);
		return *this;
	}

	vec4& vec4::operator-=(float scalar)
	{
		this->x -= (scalar);
		this->y -= (scalar);
		this->z -= (scalar);
		this->w -= (scalar);
		return *this;
	}

	vec4& vec4::operator-=(vec4 const& v)
	{
		this->x -= (v.x);
		this->y -= (v.y);
		this->z -= (v.z);
		this->w -= (v.w);
		return *this;
	}

	vec4& vec4::operator*=(float scalar)
	{
		this->x *= (scalar);
		this->y *= (scalar);
		this->z *= (scalar);
		this->w *= (scalar);
		return *this;
	}

	vec4& vec4::operator*=(vec4 const& v)
	{
		this->x *= (v.x);
		this->y *= (v.y);
		this->z *= (v.z);
		this->w *= (v.w);
		return *this;
	}

	vec4& vec4::operator/=(float v)
	{
		this->x /= (v);
		this->y /= (v);
		this->z /= (v);
		this->w /= (v);
		return *this;
	}

	vec4& vec4::operator/=(vec4 const& v)
	{
		this->x /= (v.x);
		this->y /= (v.y);
		this->z /= (v.z);
		this->w /= (v.w);
		return *this;
	}

	vec4 & vec4::operator++()
	{
		++this->x;
		++this->y;
		++this->z;
		++this->w;
		return *this;
	}

	vec4 & vec4::operator--()
	{
		--this->x;
		--this->y;
		--this->z;
		--this->w;
		return *this;
	}

	vec4 vec4::operator++(int)
	{
		vec4 Result(*this);
		++*this;
		return Result;
	}

	vec4 vec4::operator--(int)
	{
		vec4 Result(*this);
		--*this;
		return Result;
	}

	vec4 operator+(vec4 const& v)
	{
		return v;
	}

	vec4 operator-(vec4 const& v)
	{
		return vec4(0) -= v;
	}

	vec4 operator+(vec4 const& v, float const & scalar)
	{
		return vec4(v) += scalar;
	}

	vec4 operator+(float scalar, vec4 const& v)
	{
		return vec4(v) += scalar;
	}

	vec4 operator+(vec4 const& v1, vec4 const& v2)
	{
		return vec4(v1) += v2;
	}

	vec4 operator-(vec4 const& v, float const & scalar)
	{
		return vec4(v) -= scalar;
	}

	vec4 operator-(float scalar, vec4 const& v)
	{
		return vec4(scalar) -= v;
	}

	vec4 operator-(vec4 const& v1, vec4 const& v2)
	{
		return vec4(v1) -= v2;
	}

	vec4 operator*(vec4 const& v, float const & scalar)
	{
		return vec4(v) *= scalar;
	}

	vec4 operator*(float scalar, vec4 const& v)
	{
		return vec4(v) *= scalar;
	}

	vec4 operator*(vec4 const& v1, vec4 const& v2)
	{
		return vec4(v1) *= v2;
	}

	vec4 operator/(vec4 const& v, float const & scalar)
	{
		return vec4(v) /= scalar;
	}

	vec4 operator/(float scalar, vec4 const& v)
	{
		return vec4(scalar) /= v;
	}

	vec4 operator/(vec4 const& v1, vec4 const& v2)
	{
		return vec4(v1) /= v2;
	}

	bool operator==(vec4 const& v1, vec4 const& v2)
	{
		return
			detail::compute_equal<float, std::numeric_limits<float>::is_iec559>::call(v1.x, v2.x) &&
			detail::compute_equal<float, std::numeric_limits<float>::is_iec559>::call(v1.y, v2.y) &&
			detail::compute_equal<float, std::numeric_limits<float>::is_iec559>::call(v1.z, v2.z)&&
			detail::compute_equal<float, std::numeric_limits<float>::is_iec559>::call(v1.w, v2.w);
	}

	bool operator!=(vec4 const& v1, vec4 const& v2)
	{
		return !(v1 == v2);
	}

};