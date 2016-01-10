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
#include "mathlib.h"

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
