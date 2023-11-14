#pragma once
#include "vec3.hpp"
#include "mat2x2.hpp"

namespace glm {
	struct mat3 {
		typedef vec3 col_type;
		typedef vec3 row_type;
		typedef mat3 type;
		typedef mat3 transpose_type;
		typedef float value_type;
	private:
		col_type value[3];
	
	public:
		col_type & operator[](int i);
		col_type const& operator[](int i) const;

		mat3();
		mat3(mat3 const& m);
		mat3(float scalar);
		mat3(float x0, float y0, float z0,
			 float x1, float y1, float z1,
			 float x2, float y2, float z2);
		mat3(col_type const& v0,
			 col_type const& v1,
			 col_type const& v2);
		mat3(mat2 const& x);

		mat3 & operator=(mat3 const& m);
		mat3 & operator+=(float s);
		mat3 & operator+=(mat3 const& m);
		mat3 & operator-=(float s);
		mat3 & operator-=(mat3 const& m);
		mat3 & operator*=(float s);
		mat3 & operator*=(mat3 const& m);
		mat3 & operator/=(float s);
		mat3 & operator/=(mat3 const& m);

		mat3 & operator++();
		mat3 & operator--();
		mat3 operator++(int);
		mat3 operator--(int);
	};

	mat3 operator+(mat3 const& m);
	mat3 operator-(mat3 const& m);

	mat3 operator+(mat3 const& m, float scalar);
	mat3 operator+(float scalar, mat3 const& m);
	mat3 operator+(mat3 const& m1, mat3 const& m2);
	mat3 operator-(mat3 const& m, float scalar);
	mat3 operator-(float scalar, mat3 const& m);
	mat3 operator-(mat3 const& m1, mat3 const& m2);
	mat3 operator*(mat3 const& m, float scalar);
	mat3 operator*(float scalar, mat3 const& m);
	typename mat3::col_type operator*(mat3 const& m, typename mat3::row_type const& v);
	typename mat3::row_type operator*(typename mat3::col_type const& v, mat3 const& m);
	mat3 operator*(mat3 const& m1, mat3 const& m2);
	mat3 operator/(mat3 const& m, float scalar);
	mat3 operator/(float scalar, mat3 const& m);
	typename mat3::col_type operator/(mat3 const& m, typename mat3::row_type const& v);
	typename mat3::row_type operator/(typename mat3::col_type const& v, mat3 const& m);
	mat3 operator/(mat3 const& m1, mat3 const& m2);
}