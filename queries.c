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

#define EPSILON (1.0f / (1024.0f * 1024.f))

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
closest_on_segment3(segment3_t seg, vec3_t pt) {
    vec3_t  seg_dir	= vec3_sub(seg.e, seg.s);
    vec3_t  pt_dir	= vec3_sub(pt, seg.s);


    float d_sp      = vec3_dot(seg_dir, pt_dir);
    float d_ss      = vec3_dot(seg_dir, seg_dir);	// remember, always > 0

    if( d_sp < 0.0f )
        return seg.s;
    else if( d_sp > d_ss )
        return seg.e;

    float t = d_sp / d_ss; // should be float ?

    // proj	= seg.start + t * seg_dir;
    return vec3_add(vec3_mulf(seg_dir, t), seg.s);
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
distance_to_segment3(segment3_t seg, vec3_t pt) {

    vec3_t  seg_dir	= vec3_sub(seg.e, seg.s);
    vec3_t  pt_dir  = vec3_sub(pt, seg.s);

    float   d_sp    = vec3_dot(seg_dir, pt_dir);
    float   d_ss    = vec3_dot(seg_dir, seg_dir);	// remember, always > 0

    if( d_sp < 0.0f )
        return vec3_length(pt_dir);
    else if( d_sp > d_ss )
        return vec3_length(vec3_sub(pt, seg.e));

    float   t   = d_sp / d_ss;	// should be float ?

    // proj	= seg.start + t * seg_dir;
    return vec3_length(vec3_sub(pt,
                                vec3_add(seg.s,
                                         vec3_mulf(seg_dir, t))));
}

///
/// distance between a point and a plane
///
float
distance_to_plane(plane_t p, vec3_t pt) {
    vec3_t  n       = plane_normal(p);
    float   nom     = vec3_dot(pt, n) + p.d;
    float   denom   = vec3_dot(n, n);
    return FABS(nom) / denom;
}

bool
plane_from_lines(line3_t l0, line3_t l1, plane_t* out0, plane_t* out1) {
    vec3_t  n   = vec3_cross(l0.direction, l1.direction);
    if( FABS(vec3_dot(n, n)) < EPSILON * EPSILON ) {
        // rays are parallel/overlapping
        vec3_t  p0, p1;
        line3_line3_shortest_segment(l0, l1, &p0, &p1);
        n   = vec3_sub(p1, p0);
        if( vec3_length(n) < EPSILON ) {
            // pick a normal
            vec3_t  d   = l0.direction;
            float   m   = MIN(d.x, MIN(d.y, d.z));

            // take the shortest axis as the normal
            if( m == d.x ) {
                n  = vec3(1.0f, 0.0f, 0.0f);
            } else if( m == d.y ) {
                n = vec3(0.0f, 1.0f, 0.0f);
            } else {
                n = vec3(0.0f, 0.0f, 1.0f);
            }
        }
    }

    n           = vec3_normalize(n);

    *out0       = plane_from(n, -vec3_dot(l0.p, n));
    *out1       = plane_from(n, -vec3_dot(l1.p, n));
    return true;
}

float
line3_line3_distance(line3_t l0, line3_t l1) {
    vec3_t  p0, p1;
    line3_line3_shortest_segment(l0, l1, &p0, &p1);
    return vec3_length(vec3_sub(p1, p0));
}

vec2_t
closest_point_on_segment2(vec2_t start, vec2_t end, vec2_t pt) {
    vec2_t  seg_dir = vec2_sub(end, start);
    vec2_t  pt_dir  = vec2_sub(pt, start);

    float   d_sp    = vec2_dot(seg_dir, pt_dir);
    float   d_ss    = vec2_dot(seg_dir, seg_dir);

    if( d_sp < 0.0f ) {
        return start;
    } else if( d_sp > d_ss ) {
        return end;
    }

    float   t   = d_sp / d_ss;
    return vec2_add(start, vec2_mulf(seg_dir, t));
}

vec3_t
closest_point_on_segment3(segment3_t seg, vec3_t pt)  {
    vec3_t  seg_dir = vec3_sub(seg.e, seg.s);
    vec3_t  pt_dir  = vec3_sub(pt, seg.s);

    float   d_sp    = vec3_dot(seg_dir, pt_dir);
    float   d_ss    = vec3_dot(seg_dir, seg_dir);

    if( d_sp < 0.0f ) {
        return seg.s;
    } else if( d_sp > d_ss ) {
        return seg.e;
    }

    float   t   = d_sp / d_ss;
    return vec3_add(seg.s, vec3_mulf(seg_dir, t));
}

vec2_t
closest_point_on_line2(line2_t l, vec2_t pt) {
    vec2_t  pt_dir  = vec2_sub(pt, l.p);

    float   d_lp    = vec2_dot(l.direction, pt_dir);
    float   d_dd    = vec2_dot(l.direction, l.direction);

    float   t   = d_lp / d_dd;
    return vec2_add(l.p, vec2_mulf(l.direction, t));
}

vec3_t
closest_point_on_line3(line3_t l, vec3_t pt) {
    vec3_t  pt_dir  = vec3_sub(pt, l.p);

    float   d_lp    = vec3_dot(l.direction, pt_dir);
    float   d_dd    = vec3_dot(l.direction, l.direction);

    float   t   = d_lp / d_dd;
    return vec3_add(l.p, vec3_mulf(l.direction, t));
}

float
distance_point_to_segment2(vec2_t start, vec2_t end, vec2_t pt) {
    vec2_t  closest = closest_on_segment2(start, end, pt);
    return vec2_length(vec2_sub(closest, pt));
}

float
distance_point_to_segment3(segment3_t seg, vec3_t pt) {
    vec3_t  closest = closest_on_segment3(seg, pt);
    return vec3_length(vec3_sub(closest, pt));
}

float
distance_point_to_line2(line2_t l, vec2_t pt) {
    vec2_t  closest = closest_point_on_line2(l, pt);
    return vec2_length(vec2_sub(closest, pt));
}

float
distance_point_to_line3(line3_t l, vec3_t pt) {
    vec3_t  closest = closest_point_on_line3(l, pt);
    return vec3_length(vec3_sub(closest, pt));
}

bool
line3_line3_shortest_segment(line3_t l0, line3_t l1, vec3_t* out0, vec3_t* out1) {
    vec3_t      n   = vec3_cross(l0.direction, l1.direction);

    // when || n || < epsilon, either the lines are parallel or they are overlapping
    if( vec3_dot(n, n) < EPSILON * EPSILON ) {
        *out0   = closest_point_on_line3(l0, l1.p);
        *out1   = closest_point_on_line3(l1, *out0);
        return false;
    }

    mat3_t      m   = mat3(l0.direction.x, l0.direction.y, l0.direction.z,
                           l1.direction.x, l1.direction.y, l1.direction.z,
                           n.x, n.y, n.z);
    mat3_t      inv_m   = mat3_inverse(m);

    // project points to the new coordinate system
    vec3_t      p0  = mat3_mul_vec3(inv_m, l0.p);
    vec3_t      p1  = mat3_mul_vec3(inv_m, l1.p);

    vec3_t      p   = vec3(p0.x, p1.y, 0.0f);

    // now project back to the old coordinate system
    *out0   = mat3_mul_vec3(m, vec3(p.x, p.y, p0.z));
    *out1   = mat3_mul_vec3(m, vec3(p.x, p.y, p1.z));
    return true;
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
project_to_plane(plane_t p, vec3_t pt) {
    vec3_t  invN    = vec3_mulf(plane_normal(p), -1.0f);
    ray3_t  ray     = ray3_from(pt, invN);
    vec3_t  out     = pt;
    plane_ray3_intersection(p, ray, &out);
    return out;
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

    if (u < -EPSILON || u > 1.0f + EPSILON) {
        return false; // NoIntersection
    }

    // calculate V parameter and test bounds
    float v = vec3_dot(r.direction, qvec) / det;
    if (v < -EPSILON || u + v > 1.0f + 2.0f * EPSILON) {
        return false; // NoIntersection
    }

    float t = vec3_dot(edge2, qvec) / det;
    *out = vec3_add(r.start, vec3_mulf(r.direction, t));
    return true; //Intersect
}

bool
intersect_box3_sphere(box3_t b, vec3_t c, float r) {
    float dist = 0.0f;

    if (c.x < b.min.x) { dist += sqrf(c.x - b.min.x); }
    else if (c.x > b.max.x) { dist += sqrf(c.x - b.max.x); }

    if (c.y < b.min.y) { dist += sqrf(c.y - b.min.y); }
    else if (c.y > b.max.y) { dist += sqrf(c.y - b.max.y); }

    if (c.z < b.min.z) { dist += sqrf(c.z - b.min.z); }
    else if (c.z > b.max.z) { dist += sqrf(c.z - b.max.z); }

    return r * r > dist;
}

static inline
bool
is_in_0_1_range(float x) {
    return x >= 0.0f && x <= 1.0f;
}

bool
intersect_tri3_sphere(vec3_t v0, vec3_t v1, vec3_t v2, vec3_t center, float radius) {
    vec3_t  uvw = tri3_get_point_barycentric_coordinates(v0, v1, v2, center);
    if( is_in_0_1_range(uvw.x) && is_in_0_1_range(uvw.y) && is_in_0_1_range(uvw.z) ) {
        plane_t p   = tri3_plane(v0, v1, v2);
        if( distance_to_plane(p, center) <= radius ) {
            return true;
        } else {
            return false;
        }
    } else {    // point is outside, check the distance from center to segments
        float   d0  = distance_to_segment3(segment3(v0, v1), center);
        float   d1  = distance_to_segment3(segment3(v1, v2), center);
        float   d2  = distance_to_segment3(segment3(v2, v0), center);
        float   m   = MIN(d0, MIN(d1, d2));
        if( m <= radius ) {
            return true;
        } else {
            return false;
        }
    }
}
