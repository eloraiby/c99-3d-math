/*
** 3D math library Copyright 2015(c) Wael El Oraiby. All Rights Reserved
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** Under Section 7 of GPL version 3, you are granted additional
** permissions described in the GCC Runtime Library Exception, version
** 3.1, as published by the Free Software Foundation.
**
** You should have received a copy of the GNU General Public License and
** a copy of the GCC Runtime Library Exception along with this program;
** see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
** <http://www.gnu.org/licenses/>.
**
*/

#include "mathlib.h"


mat2_t
mat2_transpose(mat2_t m) {
	float	m00 = m.col[0].x;
	float	m10 = m.col[0].y;

	float	m01 = m.col[1].x;
	float	m11 = m.col[1].y;

	return mat2(m00, m01, m10, m11);
}


mat3_t
mat3_transpose(mat3_t m) {
	float	m00 = m.col[0].x;
	float	m10 = m.col[0].y;
	float	m20 = m.col[0].z;

	float	m01 = m.col[1].x;
	float	m11 = m.col[1].y;
	float	m21 = m.col[1].z;

	float	m02 = m.col[2].x;
	float	m12 = m.col[2].y;
	float	m22 = m.col[2].z;

	return mat3(m00, m01, m02,
		    m10, m11, m12,
		    m20, m21, m22);
}


mat4_t
mat4_transpose(mat4_t m) {
	float	m00 = m.col[0].x;
	float	m10 = m.col[0].y;
	float	m20 = m.col[0].z;
	float	m30 = m.col[0].w;

	float	m01 = m.col[1].x;
	float	m11 = m.col[1].y;
	float	m21 = m.col[1].z;
	float	m31 = m.col[1].w;

	float	m02 = m.col[2].x;
	float	m12 = m.col[2].y;
	float	m22 = m.col[2].z;
	float	m32 = m.col[2].w;

	float	m03 = m.col[3].x;
	float	m13 = m.col[3].y;
	float	m23 = m.col[3].z;
	float	m33 = m.col[3].w;

	return mat4(m00, m01, m02, m03,
		    m10, m11, m12, m13,
		    m20, m21, m22, m23,
		    m30, m31, m32, m33);
}

mat2_t
mat2_mulm(mat2_t a, mat2_t b) {
	float	a00 = a.col[0].x;
	float	a10 = a.col[0].y;
	float	a01 = a.col[1].x;
	float	a11 = a.col[1].y;

	float	b00 = b.col[0].x;
	float	b10 = b.col[0].y;
	float	b01 = b.col[1].x;
	float	b11 = b.col[1].y;

	float	c00 = a00 * b00 + a01 * b10;
	float	c01 = a00 * b01 + a01 * b11;
	float	c10 = a10 * b00 + a11 * b10;
	float	c11 = a10 * b01 + a11 * b11;

	return mat2(c00, c10, c01, c11);
}


mat3_t
mat3_mulm(mat3_t a, mat3_t b) {
	float	a00 = a.col[0].x;
	float	a10 = a.col[0].y;
	float	a20 = a.col[0].z;

	float	a01 = a.col[1].x;
	float	a11 = a.col[1].y;
	float	a21 = a.col[1].z;

	float	a02 = a.col[2].x;
	float	a12 = a.col[2].y;
	float	a22 = a.col[2].z;

	float	b00 = b.col[0].x;
	float	b10 = b.col[0].y;
	float	b20 = b.col[0].z;

	float	b01 = b.col[1].x;
	float	b11 = b.col[1].y;
	float	b21 = b.col[1].z;

	float	b02 = b.col[2].x;
	float	b12 = b.col[2].y;
	float	b22 = b.col[2].z;

	float	c00 = a00 * b00 + a01 * b10 + a02 * b20;
	float	c01 = a00 * b01 + a01 * b11 + a02 * b21;
	float	c02 = a00 * b02 + a01 * b12 + a02 * b22;

	float	c10 = a10 * b00 + a11 * b10 + a12 * b20;
	float	c11 = a10 * b01 + a11 * b11 + a12 * b21;
	float	c12 = a10 * b02 + a11 * b12 + a12 * b22;

	float	c20 = a20 * b00 + a21 * b10 + a22 * b20;
	float	c21 = a20 * b01 + a21 * b11 + a22 * b21;
	float	c22 = a20 * b02 + a21 * b12 + a22 * b22;

	return mat3(c00, c10, c20,
		    c01, c11, c21,
		    c02, c12, c22);
}


mat4_t
mat4_mulm(mat4_t a, mat4_t b) {
	float	a00 = a.col[0].x;
	float	a10 = a.col[0].y;
	float	a20 = a.col[0].z;
	float	a30 = a.col[0].w;

	float	a01 = a.col[1].x;
	float	a11 = a.col[1].y;
	float	a21 = a.col[1].z;
	float	a31 = a.col[1].w;

	float	a02 = a.col[2].x;
	float	a12 = a.col[2].y;
	float	a22 = a.col[2].z;
	float	a32 = a.col[2].w;

	float	a03 = a.col[3].x;
	float	a13 = a.col[3].y;
	float	a23 = a.col[3].z;
	float	a33 = a.col[3].w;

	float	b00 = b.col[0].x;
	float	b10 = b.col[0].y;
	float	b20 = b.col[0].z;
	float	b30 = b.col[0].w;

	float	b01 = b.col[1].x;
	float	b11 = b.col[1].y;
	float	b21 = b.col[1].z;
	float	b31 = b.col[1].w;

	float	b02 = b.col[2].x;
	float	b12 = b.col[2].y;
	float	b22 = b.col[2].z;
	float	b32 = b.col[2].w;

	float	b03 = b.col[3].x;
	float	b13 = b.col[3].y;
	float	b23 = b.col[3].z;
	float	b33 = b.col[3].w;

	float	c00 = a00 * b00 + a01 * b10 + a02 * b20 + a03 * b30;
	float	c01 = a00 * b01 + a01 * b11 + a02 * b21 + a03 * b31;
	float	c02 = a00 * b02 + a01 * b12 + a02 * b22 + a03 * b32;
	float	c03 = a00 * b03 + a01 * b13 + a02 * b23 + a03 * b33;

	float	c10 = a10 * b00 + a11 * b10 + a12 * b20 + a13 * b30;
	float	c11 = a10 * b01 + a11 * b11 + a12 * b21 + a13 * b31;
	float	c12 = a10 * b02 + a11 * b12 + a12 * b22 + a13 * b32;
	float	c13 = a10 * b03 + a11 * b13 + a12 * b23 + a13 * b33;

	float	c20 = a20 * b00 + a21 * b10 + a22 * b20 + a23 * b30;
	float	c21 = a20 * b01 + a21 * b11 + a22 * b21 + a23 * b31;
	float	c22 = a20 * b02 + a21 * b12 + a22 * b22 + a23 * b32;
	float	c23 = a20 * b03 + a21 * b13 + a22 * b23 + a23 * b33;

	float	c30 = a30 * b00 + a31 * b10 + a32 * b20 + a33 * b30;
	float	c31 = a30 * b01 + a31 * b11 + a32 * b21 + a33 * b31;
	float	c32 = a30 * b02 + a31 * b12 + a32 * b22 + a33 * b32;
	float	c33 = a30 * b03 + a31 * b13 + a32 * b23 + a33 * b33;

	return mat4(c00, c10, c20, c30,
		    c01, c11, c21, c31,
		    c02, c12, c22, c32,
		    c03, c13, c23, c33);
}

/// @}

/// @name matrix determinant
/// @{

float
mat2_determinant(mat2_t m) {
	float	m00 = m.col[0].x;
	float	m10 = m.col[0].y;

	float	m01 = m.col[1].x;
	float	m11 = m.col[1].y;

	float	res = m00 * m11 - m01 * m10;
	return res;
}


/// determinant

float
mat3_determinant(mat3_t m) {
	float	m00 = m.col[0].x;
	float	m10 = m.col[0].y;
	float	m20 = m.col[0].z;

	float	m01 = m.col[1].x;
	float	m11 = m.col[1].y;
	float	m21 = m.col[1].z;

	float	m02 = m.col[2].x;
	float	m12 = m.col[2].y;
	float	m22 = m.col[2].z;

	float	res = (m00 * m11 * m22 +
		       m01 * m12 * m20 +
		       m02 * m10 * m21 -
		       m00 * m12 * m21 -
		       m01 * m10 * m22 -
		       m02 * m11 * m20);
	return res;

}


float
mat4_determinant(mat4_t m) {
	float	m00 = m.col[0].x;
	float	m10 = m.col[0].y;
	float	m20 = m.col[0].z;
	float	m30 = m.col[0].w;

	float	m01 = m.col[1].x;
	float	m11 = m.col[1].y;
	float	m21 = m.col[1].z;
	float	m31 = m.col[1].w;

	float	m02 = m.col[2].x;
	float	m12 = m.col[2].y;
	float	m22 = m.col[2].z;
	float	m32 = m.col[2].w;

	float	m03 = m.col[3].x;
	float	m13 = m.col[3].y;
	float	m23 = m.col[3].z;
	float	m33 = m.col[3].w;

	float	res = (m03 * m12 * m21 * m30 - m02 * m13 * m21 * m30 -
		       m03 * m11 * m22 * m30 + m01 * m13 * m22 * m30 +
		       m02 * m11 * m23 * m30 - m01 * m12 * m23 * m30 -
		       m03 * m12 * m20 * m31 + m02 * m13 * m20 * m31 +
		       m03 * m10 * m22 * m31 - m00 * m13 * m22 * m31 -
		       m02 * m10 * m23 * m31 + m00 * m12 * m23 * m31 +
		       m03 * m11 * m20 * m32 - m01 * m13 * m20 * m32 -
		       m03 * m10 * m21 * m32 + m00 * m13 * m21 * m32 +
		       m01 * m10 * m23 * m32 - m00 * m11 * m23 * m32 -
		       m02 * m11 * m20 * m33 + m01 * m12 * m20 * m33 +
		       m02 * m10 * m21 * m33 - m00 * m12 * m21 * m33 -
		       m01 * m10 * m22 * m33 + m00 * m11 * m22 * m33);
	return res;
}
/// @}

/// @name matrix inverse
/// @{

mat2_t
mat2_inverse(mat2_t m) {
	float	m00 = m.col[0].x;
	float	m10 = m.col[0].y;

	float	m01 = m.col[1].x;
	float	m11 = m.col[1].y;

	float	inv_det = 1.0f / (m00 * m11 - m01 * m10);

	float	r00 = m11 * inv_det;
	float	r01 = -m01 * inv_det;
	float	r10 = -m10 * inv_det;
	float	r11 = m00 * inv_det;

	return mat2(r00, r10, r01, r11);
}


mat3_t
mat3_inverse(mat3_t m) {
	float	m00 = m.col[0].x;
	float	m10 = m.col[0].y;
	float	m20 = m.col[0].z;

	float	m01 = m.col[1].x;
	float	m11 = m.col[1].y;
	float	m21 = m.col[1].z;

	float	m02 = m.col[2].x;
	float	m12 = m.col[2].y;
	float	m22 = m.col[2].z;

	float	inv_det = 1.0f / (m00 * m11 * m22 +
				  m01 * m12 * m20 +
				  m02 * m10 * m21 -
				  m00 * m12 * m21 -
				  m01 * m10 * m22 -
				  m02 * m11 * m20);

	float	r00 = (m11 * m22 - m12 * m21) * inv_det;
	float	r01 = (m02 * m21 - m01 * m22) * inv_det;
	float	r02 = (m01 * m12 - m02 * m11) * inv_det;
	float	r10 = (m12 * m20 - m10 * m22) * inv_det;
	float	r11 = (m00 * m22 - m02 * m20) * inv_det;
	float	r12 = (m02 * m10 - m00 * m12) * inv_det;
	float	r20 = (m10 * m21 - m11 * m20) * inv_det;
	float	r21 = (m01 * m20 - m00 * m21) * inv_det;
	float	r22 = (m00 * m11 - m01 * m10) * inv_det;

	return mat3(r00, r10, r20, r01, r11, r21, r02, r12, r22);
}


mat4_t
mat4_inverse(mat4_t m) {
	float	m00 = m.col[0].x;
	float	m10 = m.col[0].y;
	float	m20 = m.col[0].z;
	float	m30 = m.col[0].w;

	float	m01 = m.col[1].x;
	float	m11 = m.col[1].y;
	float	m21 = m.col[1].z;
	float	m31 = m.col[1].w;

	float	m02 = m.col[2].x;
	float	m12 = m.col[2].y;
	float	m22 = m.col[2].z;
	float	m32 = m.col[2].w;

	float	m03 = m.col[3].x;
	float	m13 = m.col[3].y;
	float	m23 = m.col[3].z;
	float	m33 = m.col[3].w;

	float	denom	= (m03 * m12 * m21 * m30 - m02 * m13 * m21 * m30 -
			   m03 * m11 * m22 * m30 + m01 * m13 * m22 * m30 +
			   m02 * m11 * m23 * m30 - m01 * m12 * m23 * m30 -
			   m03 * m12 * m20 * m31 + m02 * m13 * m20 * m31 +
			   m03 * m10 * m22 * m31 - m00 * m13 * m22 * m31 -
			   m02 * m10 * m23 * m31 + m00 * m12 * m23 * m31 +
			   m03 * m11 * m20 * m32 - m01 * m13 * m20 * m32 -
			   m03 * m10 * m21 * m32 + m00 * m13 * m21 * m32 +
			   m01 * m10 * m23 * m32 - m00 * m11 * m23 * m32 -
			   m02 * m11 * m20 * m33 + m01 * m12 * m20 * m33 +
			   m02 * m10 * m21 * m33 - m00 * m12 * m21 * m33 -
			   m01 * m10 * m22 * m33 + m00 * m11 * m22 * m33);
	float	inv_det = 1.0f / denom;

	float	r00 = (m12 * m23 * m31 - m13 * m22 * m31 +
		       m13 * m21 * m32 - m11 * m23 * m32 -
		       m12 * m21 * m33 + m11 * m22 * m33) * inv_det;

	float	r01 = (m03 * m22 * m31 - m02 * m23 * m31 -
		       m03 * m21 * m32 + m01 * m23 * m32 +
		       m02 * m21 * m33 - m01 * m22 * m33) * inv_det;

	float	r02 = (m02 * m13 * m31 - m03 * m12 * m31 +
		       m03 * m11 * m32 - m01 * m13 * m32 -
		       m02 * m11 * m33 + m01 * m12 * m33) * inv_det;

	float	r03 = (m03 * m12 * m21 - m02 * m13 * m21 -
		       m03 * m11 * m22 + m01 * m13 * m22 +
		       m02 * m11 * m23 - m01 * m12 * m23) * inv_det;

	float	r10 = (m13 * m22 * m30 - m12 * m23 * m30 -
		       m13 * m20 * m32 + m10 * m23 * m32 +
		       m12 * m20 * m33 - m10 * m22 * m33) * inv_det;

	float	r11 = (m02 * m23 * m30 - m03 * m22 * m30 +
		       m03 * m20 * m32 - m00 * m23 * m32 -
		       m02 * m20 * m33 + m00 * m22 * m33) * inv_det;

	float	r12 = (m03 * m12 * m30 - m02 * m13 * m30 -
		       m03 * m10 * m32 + m00 * m13 * m32 +
		       m02 * m10 * m33 - m00 * m12 * m33) * inv_det;

	float	r13 = (m02 * m13 * m20 - m03 * m12 * m20 +
		       m03 * m10 * m22 - m00 * m13 * m22 -
		       m02 * m10 * m23 + m00 * m12 * m23) * inv_det;

	float	r20 = (m11 * m23 * m30 - m13 * m21 * m30 +
		       m13 * m20 * m31 - m10 * m23 * m31 -
		       m11 * m20 * m33 + m10 * m21 * m33) * inv_det;

	float	r21 = (m03 * m21 * m30 - m01 * m23 * m30 -
		       m03 * m20 * m31 + m00 * m23 * m31 +
		       m01 * m20 * m33 - m00 * m21 * m33) * inv_det;

	float	r22 = (m01 * m13 * m30 - m03 * m11 * m30 +
		       m03 * m10 * m31 - m00 * m13 * m31 -
		       m01 * m10 * m33 + m00 * m11 * m33) * inv_det;

	float	r23 = (m03 * m11 * m20 - m01 * m13 * m20 -
		       m03 * m10 * m21 + m00 * m13 * m21 +
		       m01 * m10 * m23 - m00 * m11 * m23) * inv_det;

	float	r30 = (m12 * m21 * m30 - m11 * m22 * m30 -
		       m12 * m20 * m31 + m10 * m22 * m31 +
		       m11 * m20 * m32 - m10 * m21 * m32) * inv_det;

	float	r31 = (m01 * m22 * m30 - m02 * m21 * m30 +
		       m02 * m20 * m31 - m00 * m22 * m31 -
		       m01 * m20 * m32 + m00 * m21 * m32) * inv_det;

	float	r32 = (m02 * m11 * m30 - m01 * m12 * m30 -
		       m02 * m10 * m31 + m00 * m12 * m31 +
		       m01 * m10 * m32 - m00 * m11 * m32) * inv_det;

	float	r33 = (m01 * m12 * m20 - m02 * m11 * m20 +
		       m02 * m10 * m21 - m00 * m12 * m21 -
		       m01 * m10 * m22 + m00 * m11 * m22) * inv_det;

	return mat4(r00, r10, r20, r30,
		    r01, r11, r21, r31,
		    r02, r12, r22, r32,
		    r03, r13, r23, r33);

}
