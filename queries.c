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

bool
plane_ray3_intersection(plane_t p, ray3_t r, vec3_t* out) {
    vec3_t	n	= plane_normal(p);
    float	t	=  -(p.d + vec3_dot(n, r.start)) / vec3_dot(n, r.direction);
    if( t < 0.0f )
        return false;
    *out	= vec3_add(r.start,
               vec3_mulf(r.direction,
                     t));
    return true;
}

vec3_t
tri3_barycentric_coordinates(vec3_t v0, vec3_t v1, vec3_t v2, vec3_t p) {
    // create a coordinate system centered around v0
    vec3_t	X	= vec3_sub(v1, v0);
    vec3_t	Y	= vec3_sub(v2, v0);
    vec3_t	Z	= vec3_cross(v0, v1);

    return vec3_add(mat3_mul_vec3(mat3(X.x, X.y, X.z,
                       Y.x, Y.y, Y.z,
                       Z.x, Z.y, Z.z),
                      p),
            v0);
}

#define EPSILON (1.0f / (1024.0f * 1024.0f))

bool
ray3_tri3_intersection(ray3_t r, vec3_t v0, vec3_t v1, vec3_t v2, vec3_t* out) {
    // find vectors for two edges sharing vert0
    vec3_t edge1 = vec3_sub(v1, v0);
    vec3_t edge2 = vec3_sub(v2, v0);

    // begin calculating determinant - also used to calculate U parameter
    vec3_t pvec = vec3_cross(r.direction, edge2);

    // if determinant is near zero, ray lies in plane of triangle
    float det = vec3_dot(edge1, pvec);

    if (det > -EPSILON && det < EPSILON) {
        return false; // Parallel
    }

    // calculate distance from vert0 to ray origin
    vec3_t	tvec = vec3_sub(r.start, v0);
    float	inv_det = 1.0f / det;

    vec3_t qvec = vec3_cross(tvec, edge1);

    float u = vec3_dot(tvec, pvec) * inv_det;

    if (u < 0.0f || u > 1.0f) {
        return false; // NoIntersection
    }

    // calculate V parameter and test bounds
    float v = vec3_dot(r.direction, qvec) * inv_det;
    if (v < 0.0f || u + v > 1.0f) {
        return false; // NoIntersection
    }

    float t = vec3_dot(edge2, qvec) * inv_det;
    *out = vec3_add(r.start, vec3_mulf(r.direction, t));
    return true; //Intersect
}
