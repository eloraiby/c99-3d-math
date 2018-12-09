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

#define EPSILON (1.0f / (16.0f * 1024.0f * 1024.f))

///
/// the projection of the point onto the segment (2D)
///
vec2_t
closest_on_segment2(vec2_t seg_start, vec2_t seg_end, vec2_t pt) {
    vec2_t  seg_dir	= vec2_sub(seg_end, seg_start);
    vec2_t  pt_dir	= vec2_sub(pt, seg_start);


    float d_sp      = vec2_dot(seg_dir, pt_dir);
    float d_ss      = vec2_dot(seg_dir, seg_dir);	// remember, always > 0

    if( d_sp < 0.0f )
        return seg_start;
    else if( d_sp > d_ss )
        return seg_end;

    float t = d_sp / d_ss; // should be float ?

    // proj	= seg.start + t * seg_dir;
    return vec2_add(vec2_mulf(seg_dir, t), seg_start);
}

///
/// the projection of the point onto the segment (3D)
///
vec3_t
closest_on_segment3(vec3_t seg_start, vec3_t seg_end, vec3_t pt) {
    vec3_t  seg_dir	= vec3_sub(seg_end, seg_start);
    vec3_t  pt_dir	= vec3_sub(pt, seg_start);


    float d_sp      = vec3_dot(seg_dir, pt_dir);
    float d_ss      = vec3_dot(seg_dir, seg_dir);	// remember, always > 0

    if( d_sp < 0.0f )
        return seg_start;
    else if( d_sp > d_ss )
        return seg_end;

    float t = d_sp / d_ss; // should be float ?

    // proj	= seg.start + t * seg_dir;
    return vec3_add(vec3_mulf(seg_dir, t), seg_start);
}

///
/// distance between a point and a segment (2D)
///
float
distance_to_segment2(vec2_t seg_start, vec2_t seg_end, vec2_t pt) {

    vec2_t  seg_dir	= vec2_sub(seg_end, seg_start);
    vec2_t  pt_dir  = vec2_sub(pt, seg_start);

    float   d_sp    = vec2_dot(seg_dir, pt_dir);
    float   d_ss    = vec2_dot(seg_dir, seg_dir);	// remember, always > 0

    if( d_sp < 0.0f )
        return vec2_length(pt_dir);
    else if( d_sp > d_ss )
        return vec2_length(vec2_sub(pt, seg_end));

    float   t   = d_sp / d_ss;	// should be float ?

    // proj	= seg.start + t * seg_dir;
    return vec2_length(vec2_sub(pt,
                                vec2_add(seg_start,
                                         vec2_mulf(seg_dir, t))));
}

///
/// distance between a point and a segment (2D)
///
float
distance_to_segment3(vec3_t seg_start, vec3_t seg_end, vec3_t pt) {

    vec3_t  seg_dir	= vec3_sub(seg_end, seg_start);
    vec3_t  pt_dir  = vec3_sub(pt, seg_start);

    float   d_sp    = vec3_dot(seg_dir, pt_dir);
    float   d_ss    = vec3_dot(seg_dir, seg_dir);	// remember, always > 0

    if( d_sp < 0.0f )
        return vec3_length(pt_dir);
    else if( d_sp > d_ss )
        return vec3_length(vec3_sub(pt, seg_end));

    float   t   = d_sp / d_ss;	// should be float ?

    // proj	= seg.start + t * seg_dir;
    return vec3_length(vec3_sub(pt,
                                vec3_add(seg_start,
                                         vec3_mulf(seg_dir, t))));
}

///
/// plane and ray intersection
///
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
tri3_point_of_barycentric_coordinates(vec3_t v0, vec3_t v1, vec3_t v2, vec3_t p) {
    mat3_t  m   = mat3(v0.x, v0.y, v0.z,
                       v1.x, v1.y, v1.z,
                       v2.x, v2.y, v2.z);

    return mat3_mul_vec3(m, vec3(p.x, p.y, 1.0f - p.x - p.y));

}

vec3_t
tri3_get_point_barycentric_coordinates(vec3_t v0, vec3_t v1, vec3_t v2, vec3_t p) {
    mat3_t  m   = mat3(v0.x, v0.y, v0.z,
                       v1.x, v1.y, v1.z,
                       v2.x, v2.y, v2.z);
    return mat3_mul_vec3(mat3_inverse(m), vec3(p.x, p.y, p.z));
}

vec2_t
tri2_point_of_barycentric_coordinates(vec2_t v0, vec2_t v1, vec2_t v2, vec2_t p) {
    mat3_t  m   = mat3(v0.x, v0.y, 1.0f,
                       v1.x, v1.y, 1.0f,
                       v2.x, v2.y, 1.0f);
    vec3_t  v   = mat3_mul_vec3(m, vec3(p.x, p.y, 1.0f - p.x - p.y));
    return vec2(v.x, v.y);
}

vec2_t
tri2_get_point_barycentric_coordinates(vec2_t v0, vec2_t v1, vec2_t v2, vec2_t p) {
    mat3_t  m   = mat3(v0.x, v0.y, 1.0f,
                       v1.x, v1.y, 1.0f,
                       v2.x, v2.y, 1.0f);
    vec3_t  v   = mat3_mul_vec3(mat3_inverse(m), vec3(p.x, p.y, 1.0f));
    return vec2(v.x, v.y);
}

/* Ray-Triangle Intersection Test Routines          */
/* Different optimizations of my and Ben Trumbore's */
/* code from journals of graphics tools (JGT)       */
/* http://www.acm.org/jgt/                          */
/* by Tomas Moller, May 2000                        */
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
    //float	inv_det = 1.0f / det;

    vec3_t qvec = vec3_cross(tvec, edge1);

    float u = vec3_dot(tvec, pvec) / det;

    if (u < 0.0f || u > 1.0f) {
        return false; // NoIntersection
    }

    // calculate V parameter and test bounds
    float v = vec3_dot(r.direction, qvec) / det;
    if (v < 0.0f || u + v > 1.0f) {
        return false; // NoIntersection
    }

    float t = vec3_dot(edge2, qvec) / det;
    *out = vec3_add(r.start, vec3_mulf(r.direction, t));
    return true; //Intersect
}
