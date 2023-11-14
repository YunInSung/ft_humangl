#include "glm.hpp"
#include <cstdlib>

namespace glm {
	mat4::mat4(): value{col_type(1, 0, 0, 0), col_type(0, 1, 0, 0), col_type(0, 0, 1, 0), col_type(0, 0, 0, 1)} {}

	mat4::mat4(mat4 const& m): value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(m[3])} {}

	mat4::mat4(float const& s) : value{col_type(s, 0, 0, 0), col_type(0, s, 0, 0), col_type(0, 0, s, 0), col_type(0, 0, 0, s)} {}

	mat4::mat4
	(
		float const& x0, float const& y0, float const& z0, float const& w0,
		float const& x1, float const& y1, float const& z1, float const& w1,
		float const& x2, float const& y2, float const& z2, float const& w2,
		float const& x3, float const& y3, float const& z3, float const& w3
	): value{
			col_type(x0, y0, z0, w0),
			col_type(x1, y1, z1, w1),
			col_type(x2, y2, z2, w2),
			col_type(x3, y3, z3, w3)} {}

	mat4::mat4(col_type const& v0, col_type const& v1, col_type const& v2, col_type const& v3) : value{col_type(v0), col_type(v1), col_type(v2), col_type(v3)} {}

	mat4::mat4(mat2 const& m): value{col_type(m[0], 0, 0), col_type(m[1], 0, 0), col_type(0, 0, 1, 0), col_type(0, 0, 0, 1)}{}

	mat4::mat4(mat3 const& m): value{col_type(m[0], 0), col_type(m[1], 0), col_type(m[2], 0), col_type(0, 0, 0, 1)} {}

	typename mat4::col_type & mat4::operator[](int i)
	{
		if (!(i >= 0 && i < 4))
			std::exit(-1);
		return this->value[i];
	}

	typename mat4::col_type const& mat4::operator[](int i) const
	{
		if (!(i >= 0 && i < 4))
			std::exit(-1);
		return this->value[i];
	}

	mat4& mat4::operator=(mat4 const& m)
	{
		this->value[0] = m[0];
		this->value[1] = m[1];
		this->value[2] = m[2];
		this->value[3] = m[3];
		return *this;
	}
	
	mat4& mat4::operator+=(float s)
	{
		this->value[0] += s;
		this->value[1] += s;
		this->value[2] += s;
		this->value[3] += s;
		return *this;
	}

	mat4& mat4::operator+=(mat4 const& m)
	{
		this->value[0] += m[0];
		this->value[1] += m[1];
		this->value[2] += m[2];
		this->value[3] += m[3];
		return *this;
	}

	mat4 & mat4::operator-=(float s)
	{
		this->value[0] -= s;
		this->value[1] -= s;
		this->value[2] -= s;
		this->value[3] -= s;
		return *this;
	}

	mat4 & mat4::operator-=(mat4 const& m)
	{
		this->value[0] -= m[0];
		this->value[1] -= m[1];
		this->value[2] -= m[2];
		this->value[3] -= m[3];
		return *this;
	}
	
	mat4 & mat4::operator*=(float s)
	{
		this->value[0] *= s;
		this->value[1] *= s;
		this->value[2] *= s;
		this->value[3] *= s;
		return *this;
	}

	mat4 & mat4::operator*=(mat4 const& m)
	{
		return (*this = *this * m);
	}

	mat4 & mat4::operator/=(float s)
	{
		this->value[0] /= s;
		this->value[1] /= s;
		this->value[2] /= s;
		this->value[3] /= s;
		return *this;
	}

	mat4 & mat4::operator/=(mat4 const& m)
	{
		return *this *= inverse(m);
	}

	mat4 & mat4::operator++()
	{
		++this->value[0];
		++this->value[1];
		++this->value[2];
		++this->value[3];
		return *this;
	}

	mat4 & mat4::operator--()
	{
		--this->value[0];
		--this->value[1];
		--this->value[2];
		--this->value[3];
		return *this;
	}

	mat4 mat4::operator++(int)
	{
		mat4 Result(*this);
		++*this;
		return Result;
	}

	mat4 mat4::operator--(int)
	{
		mat4 Result(*this);
		--*this;
		return Result;
	}

	mat4 operator+(mat4 const& m)
	{
		return m;
	}

	mat4 operator-(mat4 const& m)
	{
		return mat4(
			-m[0],
			-m[1],
			-m[2],
			-m[3]);
	}

	mat4 operator+(mat4 const& m, float const& s)
	{
		return mat4(
			m[0] + s,
			m[1] + s,
			m[2] + s,
			m[3] + s);
	}

	mat4 operator+(float const& s, mat4 const& m)
	{
		return mat4(
			m[0] + s,
			m[1] + s,
			m[2] + s,
			m[3] + s);
	}

	mat4 operator+(mat4 const& m1, mat4 const& m2)
	{
		return mat4(
			m1[0] + m2[0],
			m1[1] + m2[1],
			m1[2] + m2[2],
			m1[3] + m2[3]);
	}

	mat4 operator-(mat4 const& m, float const& s)
	{
		return mat4(
			m[0] - s,
			m[1] - s,
			m[2] - s,
			m[3] - s);
	}

	mat4 operator-(float const& s, mat4 const& m)
	{
		return mat4(
			s - m[0],
			s - m[1],
			s - m[2],
			s - m[3]);
	}

	mat4 operator-(mat4 const& m1, mat4 const& m2)
	{
		return mat4(
			m1[0] - m2[0],
			m1[1] - m2[1],
			m1[2] - m2[2],
			m1[3] - m2[3]);
	}

	mat4 operator*(mat4 const& m, float const  & s)
	{
		return mat4(
			m[0] * s,
			m[1] * s,
			m[2] * s,
			m[3] * s);
	}

	mat4 operator*(float const& s, mat4 const& m)
	{
		return mat4(
			m[0] * s,
			m[1] * s,
			m[2] * s,
			m[3] * s);
	}

	typename mat4::col_type operator*
	(
		mat4 const& m,
		typename mat4::row_type const& v
	)
	{
		typename mat4::col_type const Mov0(v[0]);
		typename mat4::col_type const Mov1(v[1]);
		typename mat4::col_type const Mul0 = m[0] * Mov0;
		typename mat4::col_type const Mul1 = m[1] * Mov1;
		typename mat4::col_type const Add0 = Mul0 + Mul1;
		typename mat4::col_type const Mov2(v[2]);
		typename mat4::col_type const Mov3(v[3]);
		typename mat4::col_type const Mul2 = m[2] * Mov2;
		typename mat4::col_type const Mul3 = m[3] * Mov3;
		typename mat4::col_type const Add1 = Mul2 + Mul3;
		typename mat4::col_type const Add2 = Add0 + Add1;
		return Add2;
	}

	typename mat4::row_type operator*
	(
		typename mat4::col_type const& v,
		mat4 const& m
	)
	{
		return typename mat4::row_type(
			m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3] * v[3],
			m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3] * v[3],
			m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3] * v[3],
			m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3] * v[3]);
	}

	mat4 operator*(mat4 const& m1, mat4 const& m2)
	{
		typename mat4::col_type const SrcA0 = m1[0];
		typename mat4::col_type const SrcA1 = m1[1];
		typename mat4::col_type const SrcA2 = m1[2];
		typename mat4::col_type const SrcA3 = m1[3];

		typename mat4::col_type const SrcB0 = m2[0];
		typename mat4::col_type const SrcB1 = m2[1];
		typename mat4::col_type const SrcB2 = m2[2];
		typename mat4::col_type const SrcB3 = m2[3];

		mat4 Result;
		Result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3];
		Result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3];
		Result[2] = SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3];
		Result[3] = SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3];
		return Result;
	}

	mat4 operator/(mat4 const& m, float const& s)
	{
		return mat4(
			m[0] / s,
			m[1] / s,
			m[2] / s,
			m[3] / s);
	}

	mat4 operator/(float const& s,	mat4 const& m)
	{
		return mat4(
			s / m[0],
			s / m[1],
			s / m[2],
			s / m[3]);
	}

	typename mat4::col_type operator/(mat4 const& m, typename mat4::row_type const& v)
	{
		return inverse(m) * v;
	}

	typename mat4::row_type operator/(typename mat4::col_type const& v, mat4 const& m)
	{
		return v * inverse(m);
	}

	mat4 operator/(mat4 const& m1, mat4 const& m2)
	{
		mat4 m1_copy(m1);
		return m1_copy /= m2;
	}

	bool operator==(mat4 const& m1, mat4 const& m2)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]) && (m1[3] == m2[3]);
	}

	bool operator!=(mat4 const& m1, mat4 const& m2)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]) || (m1[3] != m2[3]);
	}
}