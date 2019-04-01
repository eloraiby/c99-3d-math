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
#define BUILDING_3DMATH_DLL
#include "3dmath.h"

/*******************************************************************************
** conversion
*******************************************************************************/
/// verified
mat3_t
mat3_from_mat4(mat4_t m) {
    return mat3(m.col[0].x, m.col[0].y, m.col[0].z,
            m.col[1].x, m.col[1].y, m.col[1].z,
            m.col[2].x, m.col[2].y, m.col[2].z);
}

mat3_t
mat3_from_quat(quat_t q) {
    float	xx = q.x * q.x;
    float	xy = q.x * q.y;
    float	xz = q.x * q.z;
    float	xw = q.x * q.w;
    float	yy = q.y * q.y;
    float	yz = q.y * q.z;
    float	yw = q.y * q.w;
    float	zz = q.z * q.z;
    float	zw = q.z * q.w;

    float	m00 = 1.0f - 2.0f * (yy + zz);
    float	m01 = 2.0f * (xy - zw);
    float	m02 = 2.0f * (xz + yw);
    float	m10 = 2.0f * (xy + zw);
    float	m11 = 1.0f - 2.0f * (xx + zz);
    float	m12 = 2.0f * (yz - xw);
    float	m20 = 2.0f * (xz - yw);
    float	m21 = 2.0f * (yz + xw);
    float	m22 = 1.0f - 2.0f * (xx + yy);

    return mat3(m00, m10, m20, m01, m11, m21, m02, m12, m22);
}

/// verified

mat4_t
mat4_from_quat(quat_t q) {
    float	xx = q.x * q.x;
    float	xy = q.x * q.y;
    float	xz = q.x * q.z;
    float	xw = q.x * q.w;
    float	yy = q.y * q.y;
    float	yz = q.y * q.z;
    float	yw = q.y * q.w;
    float	zz = q.z * q.z;
    float	zw = q.z * q.w;

    float	m00 = 1.0f - 2.0f * (yy + zz);
    float	m01 = 2.0f * (xy - zw);
    float	m02 = 2.0f * (xz + yw);
    float	m10 = 2.0f * (xy + zw);
    float	m11 = 1.0f - 2.0f * (xx + zz);
    float	m12 = 2.0f * (yz - xw);
    float	m20 = 2.0f * (xz - yw);
    float	m21 = 2.0f * (yz + xw);
    float	m22 = 1.0f - 2.0f * (xx + yy);

    return mat4(m00, m10, m20, 0.0f,
            m01, m11, m21, 0.0f,
            m02, m12, m22, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
}


void
quat_to_axis_angle(quat_t q, vec3_t* axis, float *angle) {
    quat_t nq = quat_normalize(q);
    float	cos_a = nq.w;
    float	sin_a = sqrtf(1.0f - cos_a * cos_a);

    *angle	= acosf(cos_a) * 2.0f;

    if( fabs(sin_a) < (1.0f / 8192.0f) )
        sin_a = 1.0f;

    *axis = vec3(nq.x, nq.y, nq.z);

    *axis = vec3_divf(*axis, sin_a);
}

////////////////////////////////////////////////////////////////////////////////

quat_t
quat_from_mat3(mat3_t m) {
    quat_t	q;

    float	mat0 = m.col[0].x;
    float	mat1 = m.col[1].x;
    float	mat2 = m.col[2].x;

    float	mat4 = m.col[0].y;
    float	mat5 = m.col[1].y;
    float	mat6 = m.col[2].y;

    float	mat8 = m.col[0].z;
    float	mat9 = m.col[1].z;
    float	mat10 = m.col[2].z;

    float	t = 1.0f + mat0 + mat5 + mat10;

    if( t > 0.0f )
    {
        float s = sqrtf(t) * 2.0f;

        q.x	= (mat9 - mat6) / s;
        q.y	= (mat2 - mat8) / s;
        q.z	= (mat4 - mat1) / s;
        q.w	= 0.25f * s;
    }
    else
    {
        if( mat0 > mat5 && mat0 > mat10 )
        {
            // Column 0:
            float s = sqrtf(1.0f + mat0 - mat5 - mat10) * 2.0f;
            q.x	= 0.25f * s;
            q.y	= (mat4 + mat1) / s;
            q.z	= (mat2 + mat8) / s;
            q.w	= (mat9 - mat6) / s;
        }
        else if( mat5 > mat10 )
        {
            // Column 1:
            float s = sqrtf(1.0f + mat5 - mat0 - mat10) * 2.0f;
            q.x	= (mat4 + mat1) / s;
            q.y	= 0.25f * s;
            q.z	= (mat9 + mat6) / s;
            q.w	= (mat2 - mat8) / s;
        }
        else
        {
            // Column 2:
            float s = sqrtf(1.0f + mat10 - mat0 - mat5) * 2.0f;
            q.x	= (mat2 + mat8) / s;
            q.y	= (mat9 + mat6) / s;
            q.z	= 0.25f * s;
            q.w	= (mat4 - mat1) / s;
        }
    }

    return q;
}

/// verified

quat_t
quat_from_mat4(mat4_t m) {
    quat_t	q;
    float	mat0 = m.col[0].x;
    float	mat1 = m.col[1].x;
    float	mat2 = m.col[2].x;

    float	mat4 = m.col[0].y;
    float	mat5 = m.col[1].y;
    float	mat6 = m.col[2].y;

    float	mat8 = m.col[0].z;
    float	mat9 = m.col[1].z;
    float	mat10 = m.col[2].z;

    float	t = 1.0f + mat0 + mat5 + mat10;

    if( t > 0.0f )
    {
        float	s = sqrtf(t) * 2.0f;

        q.x	= (mat9 - mat6) / s;
        q.y	= (mat2 - mat8) / s;
        q.z	= (mat4 - mat1) / s;
        q.w	= 0.25f * s;
    }
    else
    {
        if( mat0 > mat5 && mat0 > mat10 )
        {
            // Column 0:
            float s = sqrtf(1.0f + mat0 - mat5 - mat10) * 2.0f;
            q.x	= 0.25f * s;
            q.y	= (mat4 + mat1) / s;
            q.z	= (mat2 + mat8) / s;
            q.w	= (mat9 - mat6) / s;
        }
        else if( mat5 > mat10 )
        {
            // Column 1:
            float s = sqrtf(1.0f + mat5 - mat0 - mat10) * 2.0f;
            q.x	= (mat4 + mat1) / s;
            q.y	= 0.25f * s;
            q.z	= (mat9 + mat6) / s;
            q.w	= (mat2 - mat8) / s;
        }
        else
        {
            // Column 2:
            float s = sqrtf(1.0f + mat10 - mat0 - mat5) * 2.0f;
            q.x	= (mat2 + mat8) / s;
            q.y	= (mat9 + mat6) / s;
            q.z	= 0.25f * s;
            q.w	= (mat4 - mat1) / s;
        }
    }
    return q;
}

/// verified

quat_t
quat_from_axis_angle(vec3_t axis, float angle) {
    quat_t	q;
    vec3_t	n = (vec3_length(axis) > 0.0f ) ? vec3_normalize(axis) : axis;
    float	half_angle = angle * 0.5f;
    float	sin_a = sinf(half_angle);
    float	cos_a = cosf(half_angle);

    n	= vec3_mulf(n, sin_a);

    q.x	= n.x;
    q.y	= n.y;
    q.z	= n.z;
    q.w	= cos_a;
    return q;
}
