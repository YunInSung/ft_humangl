#pragma once

#include "vec2.hpp"

namespace glm {
	struct mat2 {
		typedef vec2 col_type;
		typedef vec2 row_type;
		typedef mat2 type;
		typedef mat2 transpose_type;
	private:
		col_type value[2];
		
	public:
		col_type & operator[](int i);
		col_type const& operator[](int i) const;
		mat2();
		mat2(mat2 const& m);
		mat2(float scalar);
		mat2(float const& x1, float const& y1,
			 float const& x2, float const& y2);
		mat2(col_type const& v1,
			 col_type const& v2);

		mat2& operator=(mat2 const& m);
		mat2& operator+=(float s);
		mat2& operator+=(mat2 const& m);
		mat2& operator-=(float s);
		mat2& operator-=(mat2 const& m);
		mat2& operator*=(float s);
		mat2& operator*=(mat2 const& m);
		mat2& operator/=(float s);
		mat2& operator/=(mat2 const& m);

		mat2& operator++ ();
		mat2& operator-- ();
		mat2 operator++(int);
		mat2 operator--(int);
	};
	mat2 operator+(mat2 const& m);
	mat2 operator-(mat2 const& m);

	mat2 operator+(mat2 const& m, float scalar);
	mat2 operator+(float scalar, mat2 const& m);
	mat2 operator+(mat2 const& m1, mat2 const& m2);
	mat2 operator-(mat2 const& m, float scalar);
	mat2 operator-(float scalar, mat2 const& m);
	mat2 operator-(mat2 const& m1, mat2 const& m2);
	mat2 operator*(mat2 const& m, float scalar);
	mat2 operator*(float scalar, mat2 const& m);
	typename mat2::col_type operator*(mat2 const& m, typename mat2::row_type const& v);
	typename mat2::row_type operator*(typename mat2::col_type const& v, mat2 const& m);
	mat2 operator*(mat2 const& m1, mat2 const& m2);
	mat2 operator/(mat2 const& m, float scalar);
	mat2 operator/(float scalar, mat2 const& m);
	typename mat2::col_type operator/(mat2 const& m, typename mat2::row_type const& v);
	typename mat2::row_type operator/(typename mat2::col_type const& v, mat2 const& m);
	mat2 operator/(mat2 const& m1, mat2 const& m2);
};