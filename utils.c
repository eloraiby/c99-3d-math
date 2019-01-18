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
#include "3dmath.h"

static ivec3_t cube_table[8] = {
    { 0, 1, 0 },
    { 1, 1, 0 },
    { 1, 1, 1 },
    { 0, 1, 1 },

    { 0, 0, 0 },
    { 1, 0, 0 },
    { 1, 0, 1 },
    { 0, 0, 1 }
};

void
box3_subdivide(box3_t bbox, box3_t out[3]) {
    vec3_t  ps[2] = { bbox.min, bbox.max };

    vec3_t  vs[8];
    for( uint32_t i = 0; i < 8; ++i ) {
        vs[i] = vec3(ps[cube_table[i].x].x, ps[cube_table[i].y].y, ps[cube_table[i].z].z);
    }

    vec3_t  center = box3_center(bbox);

    for( uint32_t i = 0; i < 8; ++i ) {
        out[i] = box3(vec3_min(center, vs[i]), vec3_max(center, vs[i]));
    }
}
