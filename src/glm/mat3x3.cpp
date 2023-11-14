#include "mat3x3.hpp"
#include "glm.hpp"
#include <cstdlib>

namespace glm {
	mat3::mat3(): value{col_type(1, 0, 0), col_type(0, 1, 0), col_type(0, 0, 1)} {}

	mat3::mat3(mat3 const& m): value{col_type(m[0]), col_type(m[1]), col_type(m[2])} {}

	mat3::mat3(float s) : value{col_type(s, 0, 0), col_type(0, s, 0), col_type(0, 0, s)} {}

	mat3::mat3
	(
		float x0, float y0, float z0,
		float x1, float y1, float z1,
		float x2, float y2, float z2
	): value{col_type(x0, y0, z0), col_type(x1, y1, z1), col_type(x2, y2, z2)} {}

	mat3::mat3(col_type const& v0, col_type const& v1, col_type const& v2): value{col_type(v0), col_type(v1), col_type(v2)} {}

	mat3::mat3(mat2 const& m) : value{col_type(m[0], 0), col_type(m[1], 0), col_type(0, 0, 1)} {}

	typename mat3::col_type & mat3::operator[](int i)
	{
		if (!(i >= 0 && i < 3))
			std::exit(-1);
		return this->value[i];
	}

	typename mat3::col_type const& mat3::operator[](int i) const
	{
		if (!(i >= 0 && i < 3))
			std::exit(-1);
		return this->value[i];
	}

	mat3 & mat3::operator=(mat3 const& m)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		this->value[2] = m[2];
		return *this;
	}

	mat3 & mat3::operator+=(float s)
	{
		this->value[0] += s;
		this->value[1] += s;
		this->value[2] += s;
		return *this;
	}

	mat3 & mat3::operator+=(mat3 const& m)
	{
		this->value[0] += m[0];
		this->value[1] += m[1];
		this->value[2] += m[2];
		return *this;
	}

	mat3 & mat3::operator-=(float s)
	{
		this->value[0] -= s;
		this->value[1] -= s;
		this->value[2] -= s;
		return *this;
	}

	mat3 & mat3::operator-=(mat3 const& m)
	{
		this->value[0] -= m[0];
		this->value[1] -= m[1];
		this->value[2] -= m[2];
		return *this;
	}

	mat3 & mat3::operator*=(float s)
	{
		this->value[0] *= s;
		this->value[1] *= s;
		this->value[2] *= s;
		return *this;
	}

	mat3 & mat3::operator*=(mat3 const& m)
	{
		return (*this = *this * m);
	}

	mat3 & mat3::operator/=(float s)
	{
		this->value[0] /= s;
		this->value[1] /= s;
		this->value[2] /= s;
		return *this;
	}

	mat3 & mat3::operator/=(mat3 const& m)
	{
		return *this *= inverse(m);
	}

	mat3 & mat3::operator++()
	{
		++this->value[0];
		++this->value[1];
		++this->value[2];
		return *this;
	}

	mat3 & mat3::operator--()
	{
		--this->value[0];
		--this->value[1];
		--this->value[2];
		return *this;
	}

	mat3 mat3::operator++(int)
	{
		mat3 Result(*this);
		++*this;
		return Result;
	}

	mat3 mat3::operator--(int)
	{
		mat3 Result(*this);
		--*this;
		return Result;
	}

	mat3 operator+(mat3 const& m)
	{
		return m;
	}

	mat3 operator-(mat3 const& m)
	{
		return mat3(
			-m[0],
			-m[1],
			-m[2]);
	}

	mat3 operator+(mat3 const& m, float scalar)
	{
		return mat3(
			m[0] + scalar,
			m[1] + scalar,
			m[2] + scalar);
	}

	mat3 operator+(float scalar, mat3 const& m)
	{
		return mat3(
			m[0] + scalar,
			m[1] + scalar,
			m[2] + scalar);
	}

	mat3 operator+(mat3 const& m1, mat3 const& m2)
	{
		return mat3(
			m1[0] + m2[0],
			m1[1] + m2[1],
			m1[2] + m2[2]);
	}

	mat3 operator-(mat3 const& m, float scalar)
	{
		return mat3(
			m[0] - scalar,
			m[1] - scalar,
			m[2] - scalar);
	}

	mat3 operator-(float scalar, mat3 const& m)
	{
		return mat3(
			scalar - m[0],
			scalar - m[1],
			scalar - m[2]);
	}

	mat3 operator-(mat3 const& m1, mat3 const& m2)
	{
		return mat3(
			m1[0] - m2[0],
			m1[1] - m2[1],
			m1[2] - m2[2]);
	}

	mat3 operator*(mat3 const& m, float scalar)
	{
		return mat3(
			m[0] * scalar,
			m[1] * scalar,
			m[2] * scalar);
	}

	mat3 operator*(float scalar, mat3 const& m)
	{
		return mat3(
			m[0] * scalar,
			m[1] * scalar,
			m[2] * scalar);
	}

	typename mat3::col_type operator*(mat3 const& m, typename mat3::row_type const& v)
	{
		return typename mat3::col_type(
			m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
			m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z,
			m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z);
	}

	typename mat3::row_type operator*(typename mat3::col_type const& v, mat3 const& m)
	{
		return typename mat3::row_type(
			m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
			m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z);
	}

	mat3 operator*(mat3 const& m1, mat3 const& m2)
	{
		float const SrcA00 = m1[0][0];
		float const SrcA01 = m1[0][1];
		float const SrcA02 = m1[0][2];
		float const SrcA10 = m1[1][0];
		float const SrcA11 = m1[1][1];
		float const SrcA12 = m1[1][2];
		float const SrcA20 = m1[2][0];
		float const SrcA21 = m1[2][1];
		float const SrcA22 = m1[2][2];

		float const SrcB00 = m2[0][0];
		float const SrcB01 = m2[0][1];
		float const SrcB02 = m2[0][2];
		float const SrcB10 = m2[1][0];
		float const SrcB11 = m2[1][1];
		float const SrcB12 = m2[1][2];
		float const SrcB20 = m2[2][0];
		float const SrcB21 = m2[2][1];
		float const SrcB22 = m2[2][2];

		mat3 Result;
		Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01 + SrcA20 * SrcB02;
		Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02;
		Result[0][2] = SrcA02 * SrcB00 + SrcA12 * SrcB01 + SrcA22 * SrcB02;
		Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12;
		Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12;
		Result[1][2] = SrcA02 * SrcB10 + SrcA12 * SrcB11 + SrcA22 * SrcB12;
		Result[2][0] = SrcA00 * SrcB20 + SrcA10 * SrcB21 + SrcA20 * SrcB22;
		Result[2][1] = SrcA01 * SrcB20 + SrcA11 * SrcB21 + SrcA21 * SrcB22;
		Result[2][2] = SrcA02 * SrcB20 + SrcA12 * SrcB21 + SrcA22 * SrcB22;
		return Result;
	}

	mat3 operator/(mat3 const& m, float scalar)
	{
		return mat3(
			m[0] / scalar,
			m[1] / scalar,
			m[2] / scalar);
	}

	mat3 operator/(float scalar, mat3 const& m)
	{
		return mat3(
			scalar / m[0],
			scalar / m[1],
			scalar / m[2]);
	}

	typename mat3::col_type operator/(mat3 const& m, typename mat3::row_type const& v)
	{
		return  inverse(m) * v;
	}

	typename mat3::row_type operator/(typename mat3::col_type const& v, mat3 const& m)
	{
		return v * inverse(m);
	}

	mat3 operator/(mat3 const& m1, mat3 const& m2)
	{
		mat3 m1_copy(m1);
		return m1_copy /= m2;
	}

	bool operator==(mat3 const& m1, mat3 const& m2)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]);
	}

	bool operator!=(mat3 const& m1, mat3 const& m2)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]);
	}

}