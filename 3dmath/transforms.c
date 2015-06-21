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

////////////////////////////////////////////////////////////////////////////////
/// @name orthogonal 2d projection matrix (both tested)
/// @{
mat4_t
mat4_ortho(float left, float right, float bottom, float top) {
	return mat4_ortho4(left, right, bottom, top, -1.0f, 1.0f);
}


mat4_t
mat4_ortho2(vec2_t lb, vec2_t rt) {
	vec3_t	vl	= vec3(lb.x, lb.y, -1.0f);
	vec3_t	vr	= vec3(rt.x, rt.y,  1.0f);
	return mat4_ortho3(vl, vr);
}
/// @}

/// orthogonal 3d projection matrix (both tested)
/// @{
mat4_t
mat4_ortho4(float left, float right, float bottom, float top, float near, float far) {
	float	width	= right - left;
	float	height	= top - bottom;
	float	depth	= far - near;
	float	r00	= 2.0f / width;
	float	r11	= 2.0f / height;
	float	r22	= -2.0f / depth;
	float	r03	= -(right + left) / width;
	float	r13	= -(top + bottom) / height;
	float	r23	= -(far + near) / depth;
	return mat4(r00, 0.0f, 0.0f, 0.0f,
		    0.0f, r11, 0.0f, 0.0f,
		    0.0f, 0.0f, r22, 0.0f,
		    r03, r13, r23, 1.0f);
}

mat4_t
mat4_ortho3(vec3_t lbn, vec3_t rtf) {
	return mat4_ortho4(lbn.x, rtf.x, lbn.y, rtf.y, lbn.z, rtf.z);
}
/// @}

/// translation matrix (tested)

mat4_t
mat4_translation(vec3_t trans) {
	return mat4(1.0f, 0.0f, 0.0f, 0.0f,
		    0.0f, 1.0f, 0.0f, 0.0f,
		    0.0f, 0.0f, 1.0f, 0.0f,
		    trans.x, trans.y, trans.z, 1.0f);
}

/// scale matrix (tested)

mat4_t
mat4_scale(vec3_t scale) {
	return mat4(scale.x, 0.0f, 0.0f, 0.0f,
		    0.0f, scale.y, 0.0f, 0.0f,
		    0.0f, 0.0f, scale.z, 0.0f,
		    0.0f, 0.0f, 0.0f, 1.0f);
}

/// @name rotation matrix
/// @{

mat4_t
mat4_rotation(quat_t q) {
	return mat4_from_quat(q);
}


mat4_t
mat4_rotation2(float angle, vec3_t axis) {
	return mat4_from_quat(quat_from_axis_angle(axis, angle));
}

/// @}

/// project a point to the screen (tested)

vec3_t
vec3_project(mat4_t world, mat4_t persp, vec2_t lb, vec2_t rt, vec3_t pt) {
	vec4_t	in	= vec4(pt.x, pt.y, pt.z, 1.0f);
	mat4_t	pw	= mat4_mulm(persp, world);
	vec4_t	out	= mat4_mul_vec4(pw, in);

	out.x	/= out.w;
	out.y	/= out.w;
	out.z	/= out.w;

	vec3_t	out_v;
	out_v.x	= lb.x + ((rt.x - lb.x) * (out.x + 1.0f) * 0.5f);
	out_v.y	= lb.y + ((rt.y - lb.y) * (out.y + 1.0f) * 0.5f);
	out_v.z	= (out.z + 1.0f) * 0.5f;

	return out_v;
}


/// unproject a point to the 3d system (tested)

vec3_t
vec3_unproject(mat4_t world, mat4_t persp, vec2_t lb, vec2_t rt, vec3_t pt) {
	vec4_t	in;
	mat4_t	pw	= mat4_mulm(persp, world);
	mat4_t	inv	= mat4_inverse(pw);
	in.x	= (2.0f * (pt.x - lb.x) / (rt.x - lb.x)) - 1.0f;
	in.y	= (2.0f * (pt.y - lb.y) / (rt.y - lb.y)) - 1.0f;
	in.z	= (2.0f * pt.z) - 1.0f;
	in.w	= 1.0f;
	vec4_t	out = mat4_mul_vec4(inv, in);
	out = vec4_divf(out, out.w);
	return vec3(out.x, out.y, out.z);
}

///
/// frustum matrix (tested)
/// @param lbn left/bottom/near
/// @param rtf right/top/far
/// @return the frustum matrix
///

mat4_t
mat4_frustum(vec3_t lbn, vec3_t rtf) {
	float	width	= rtf.x - lbn.x;
	float	height	= rtf.y - lbn.y;
	float	depth	= rtf.z - lbn.z;
	float	a	= (rtf.x + lbn.x) / width;
	float	b	= (rtf.y + lbn.y) / height;
	float	c	= -(rtf.z + lbn.z) / depth;
	float	d	= -(2.0f * rtf.z * lbn.z) / depth;

	return mat4(2.0f * lbn.z / width, 0.0f, 0.0f, 0.0f,
		    0.0f, 2.0f * lbn.z / height, 0.0f, 0.0f,
		    a, b, c, -1.0f,
		    0.0f, 0.0f, d, 0.0f);
}

///
/// perspective projection matrix (tested)
/// @param fovy field of view in radians and in y direction
/// @param aspect the aspect ratio
/// @param near near plane value
/// @param far far plane value
///

mat4_t
mat4_perspective(float fovy, float aspect, float near, float far) {
	float	f	= 1.0f / tan(fovy * 0.5f);
	float	denom	= near - far;
	float	a	= (far + near) / denom;
	float	b	= (2.0f * far * near) / denom;

	return mat4(f / aspect, 0.0f, 0.0f, 0.0f,
		    0.0f, f, 0.0f, 0.0f,
		    0.0f, 0.0f, a, -1.0f,
		    0.0f, 0.0f, b, 0.0f);
}

///
/// lookat matrix (tested)
/// @param eye the eye position
/// @param dest the eye destination position
/// @param up the up vector
/// @return the lookat matrix
///

mat4_t
mat4_lookat(vec3_t eye, vec3_t dest, vec3_t up) {
	vec3_t	f	= vec3_normalize(vec3_sub(dest, eye));
	vec3_t	s	= vec3_normalize(vec3_cross(f, up));
	vec3_t	u	= vec3_normalize(vec3_cross(s, f));

	mat4_t	trans	= mat4_translation(vec3_neg(eye));

	mat4_t	m	= mat4(s.x, u.x, -f.x, 0.0f,
			       s.y, u.y, -f.y, 0.0f,
			       s.z, u.z, -f.z, 0.0f,
			       0.0f, 0.0f, 0.0f, 1.0f);
	return mat4_mulm(m, trans);
}

///
/// @brief convert from world coordinates to local coordinates
/// @param m world matrix
/// @param in the input world coordinates
/// @return local coordinates
///

vec3_t
world3_to_local3(mat4_t world, vec3_t in) {
	mat4_t	inv_world	= mat4_inverse(world);
	vec4_t	vin		= vec4(in.x, in.y, in.z, 1.0f);
	vec4_t	vout		= mat4_mul_vec4(inv_world, vin);
	return vec3(vout.x, vout.y, vout.z);
}

///
/// @brief transform a vec3 by a mat4
/// @param m matrix
/// @param in input vector
/// @return the transformed vector
///

vec3_t
transform_vec3(mat4_t m, vec3_t in) {
	vec4_t	vin	= vec4(in.x, in.y, in.z, 1.0f);
	vec4_t	vout	= mat4_mul_vec4(m, vin);
	return vec3(vout.x / vout.w, vout.y / vout.w, vout.z / vout.w);
}

///
/// @brief transform a vec4 by a mat4
/// @param m matrix
/// @param in input vector
/// @return the transformed vector
///

vec4_t
transform_vec4(mat4_t m, vec4_t in) {
	return mat4_mul_vec4(m, in);
}


bool
mat4_decompose(mat4_t m, vec3_t* scale, quat_t* rot, vec3_t* trans) {
	mat3_t	rot_matrix;
	vec3_t	col0	= vec3(m.col[0].x, m.col[0].y, m.col[0].z);
	vec3_t	col1	= vec3(m.col[1].x, m.col[1].y, m.col[1].z);
	vec3_t	col2	= vec3(m.col[2].x, m.col[2].y, m.col[2].z);
	float	det	= mat4_determinant(m);

	*scale	= vec3(vec4_length(m.col[0]), vec4_length(m.col[1]), vec4_length(m.col[2]));
	*trans	= vec3(m.col[3].x, m.col[3].y, m.col[3].z);

	if( det < 0 )
		*scale	= vec3_neg(*scale);

	if( scale->x != 0.0f )
		col0	= vec3_divf(col0, scale->x);
	if( scale->y != 0.0f )
		col1	= vec3_divf(col1, scale->y);
	if( scale->z != 0.0f )
		col2	= vec3_divf(col2, scale->z);

	rot_matrix	= mat3(col0.x, col0.y, col0.z,
			       col1.x, col1.y, col1.z,
			       col2.x, col2.y, col2.z);

	*rot	= quat_from_mat3(rot_matrix);
	return true;
}

