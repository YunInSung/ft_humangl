#pragma once
#include "vec4.hpp"
#include "mat2x2.hpp"
#include "mat3x3.hpp"

namespace glm {
	struct mat4 {
		typedef vec4 col_type;
		typedef vec4 row_type;
		typedef mat4 type;
		typedef mat4 transpose_type;
		typedef float value_type;

	private:
		col_type value[4];

	public:
		col_type & operator[](int i);
		col_type const& operator[](int i) const;

		mat4();
		mat4(mat4 const& m);
		mat4(float const& x);
		mat4(float const& x0, float const& y0, float const& z0, float const& w0,
			 float const& x1, float const& y1, float const& z1, float const& w1,
			 float const& x2, float const& y2, float const& z2, float const& w2,
			 float const& x3, float const& y3, float const& z3, float const& w3);
		mat4(col_type const& v0,
			 col_type const& v1,
			 col_type const& v2,
			 col_type const& v3);

		mat4(mat2 const& x);
		mat4(mat3 const& x);

		mat4 & operator=(mat4 const& m);
		mat4 & operator+=(float s);
		mat4 & operator+=(mat4 const& m);
		mat4 & operator-=(float s);
		mat4 & operator-=(mat4 const& m);
		mat4 & operator*=(float s);
		mat4 & operator*=(mat4 const& m);
		mat4 & operator/=(float s);
		mat4 & operator/=(mat4 const& m);

		mat4 & operator++();
		mat4 & operator--();
		mat4 operator++(int);
		mat4 operator--(int);
	};

	mat4 operator+(mat4 const& m);
	mat4 operator-(mat4 const& m);

	mat4 operator+(mat4 const& m, float const& s);
	mat4 operator+(float const& s, mat4 const& m);
	mat4 operator+(mat4 const& m1, mat4 const& m2);
	mat4 operator-(mat4 const& m, float const& s);
	mat4 operator-(float const& s, mat4 const& m);
	mat4 operator-(mat4 const& m1,	mat4 const& m2);
	mat4 operator*(mat4 const& m, float const& s);
	mat4 operator*(float const& s, mat4 const& m);
	typename mat4::col_type operator*(mat4 const& m, typename mat4::row_type const& v);
	typename mat4::row_type operator*(typename mat4::col_type const& v, mat4 const& m);
	mat4 operator*(mat4 const& m1, mat4 const& m2);
	mat4 operator/(mat4 const& m, float const& s);
	mat4 operator/(float const& s, mat4 const& m);
	typename mat4::col_type operator/(mat4 const& m, typename mat4::row_type const& v);
	typename mat4::row_type operator/(typename mat4::col_type const& v, mat4 const& m);
	mat4 operator/(mat4 const& m1,	mat4 const& m2);

	bool operator==(mat4 const& m1, mat4 const& m2);
	bool operator!=(mat4 const& m1, mat4 const& m2);
}