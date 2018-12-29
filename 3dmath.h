#ifndef _3DMATH_H
#define _3DMATH_H

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

/*
 * Parameter passing is based on the conclusions drawn from:
 *	http://www.macieira.org/blog/2012/02/the-value-of-passing-by-value/
 * These conclusions are for code running on x86-64, IA64, ARMv7, MIPS platforms:
 *
 * Quoting Thiago Macieira (2012) :
 *
 * Recommendations for code :
 * ==========================
 *
 * - Structures of up to 16 bytes containing integers and pointers should be passed by value;
 * - Homogeneous structures of up to 16 bytes containing floating-point should be passed by value (2 doubles or 4 floats);
 * - Mixed-type structures should be avoided; if they exist, passing by value is still a good idea;
 *
 * The above is only valid for structures that are trivially-copiable and trivially-destrucitble. All C structures (POD in C++) meet those criteria.
 */
#include <math.h>
#include <float.h>
#include <stdbool.h>

#if defined _WIN32 || defined __CYGWIN__
#ifdef BUILDING_3DMATH_DLL
#ifdef __GNUC__
#define DLL_3DMATH_PUBLIC __attribute__ ((dllexport))
#else
#define DLL_3DMATH_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
#endif
#else
#ifdef __GNUC__
#define DLL_3DMATH_PUBLIC __attribute__ ((dllimport))
#else
#define DLL_3DMATH_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
#endif
#endif
#define DLL_3DMATH_LOCAL
#else
#if __GNUC__ >= 4
#define DLL_3DMATH_PUBLIC __attribute__ ((visibility ("default")))
#define DLL_3DMATH_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#define DLL_3DMATH_PUBLIC
#define DLL_3DMATH_LOCAL
#endif
#endif


#ifdef _MSC_VER
#  define PACKED_STRUCT(name) \
    __pragma(pack(push, 1)) struct name __pragma(pack(pop))
#elif defined(__GNUC__)
#  define PACKED_STRUCT(name) struct __attribute__((packed)) name
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifndef M_PI
#	define M_PI		3.14159265358979323846	/* pi */
#endif

#ifndef MIN
#	define MIN(a, b)	((a < b) ? a : b)
#endif

#ifndef MAX
#	define MAX(a, b)	((a > b) ? a : b)
#endif

#ifndef INLINE
#	ifdef _MSC_VER
#		define INLINE		__forceinline
#	elif defined(__GNUC__)
#		define INLINE		inline __attribute__((gnu_inline))
#	else
#		define INLINE inline
#	endif
#endif

#ifndef WARN_UNUSED
#	ifdef _MSC_VER
#		define WARN_UNUSED
#	elif defined(__GNUC__)
#		define WARN_UNUSED	__attribute__((warn_unused_result))
#	else
#		define WARN_UNUSED
#	endif
#endif

#ifndef UNUSED
#	ifdef _MSC_VER
#		define UNUSED
#	elif defined(__GNUC__)
#		define UNUSED		__attribute__((unused))
#	else
#		define UNUSED
#	endif
#endif

/*******************************************************************************
**
** colors
**
*******************************************************************************/
typedef struct {
    float	r, g, b;
} color3_t;

typedef struct {
    float	r, g, b, a;
} color4_t;

static INLINE color3_t color3(float r, float g, float b)		{	color3_t ret	= { r, g, b };		return ret;	}
static INLINE color4_t color4(float r, float g, float b, float a)	{	color4_t ret	= { r, g, b, a };	return ret;	}

typedef struct {
    uint8_t r, g, b;
} color3b_t;

typedef struct {
    uint8_t r, g, b, a;
} color4b_t;

static INLINE color3b_t color3b(uint8_t r, uint8_t g, uint8_t b)            {	color3b_t ret	= { r, g, b };		return ret;	}
static INLINE color4b_t color4b(uint8_t r, uint8_t g, uint8_t b, uint8_t a)	{	color4b_t ret	= { r, g, b, a };	return ret;	}


/*******************************************************************************
** vectors
*******************************************************************************/

/* int vectors */
typedef struct {
    int	x, y;
} ivec2_t;

typedef struct {
    int	x, y, z;
} ivec3_t;

typedef struct {
    int	x, y, z, w;
} ivec4_t;

/* float vectors */
typedef struct {
    float	x, y;
} vec2_t;

typedef struct {
    float	x, y, z;
} vec3_t;

typedef struct {
    float	x, y, z, w;
} vec4_t;

/* float vectors */
typedef struct {
    double	x, y;
} dvec2_t;

typedef struct {
    double	x, y, z;
} dvec3_t;

typedef struct {
    double	x, y, z, w;
} dvec4_t;

/* constructors */
static INLINE ivec2_t ivec2(int x, int y)				{	ivec2_t	ret	= { x, y };		return ret;		}
static INLINE ivec3_t ivec3(int x, int y, int z)			{	ivec3_t	ret	= { x, y, z };		return ret;		}
static INLINE ivec4_t ivec4(int x, int y, int z, int w)		{	ivec4_t	ret	= { x, y, z, w };	return ret;		}

static INLINE vec2_t vec2(float x, float y)				{	vec2_t	ret	= { x, y };		return ret;		}
static INLINE vec3_t vec3(float x, float y, float z)			{	vec3_t	ret	= { x, y, z };		return ret;		}
static INLINE vec4_t vec4(float x, float y, float z, float w)		{	vec4_t	ret	= { x, y, z, w };	return ret;		}

static INLINE dvec2_t dvec2(double x, double y)				{	dvec2_t	ret	= { x, y };		return ret;		}
static INLINE dvec3_t dvec3(double x, double y, double z)			{	dvec3_t	ret	= { x, y, z };		return ret;		}
static INLINE dvec4_t dvec4(double x, double y, double z, double w)		{	dvec4_t	ret	= { x, y, z, w };	return ret;		}

static INLINE dvec2_t dvec2_of_vec2(vec2_t v)				{	dvec2_t	ret	= { (double)v.x, (double)v.y };		return ret;		}
static INLINE dvec3_t dvec3_of_vec3(vec3_t v)			{	dvec3_t	ret	= { (double)v.x, (double)v.y, (double)v.z };		return ret;		}
static INLINE dvec4_t dvec4_of_vec4(vec4_t v)		{	dvec4_t	ret	= { (double)v.x, (double)v.y, (double)v.z, (double)v.w };	return ret;		}

static INLINE vec2_t vec2_of_dvec2(dvec2_t v)				{	vec2_t	ret	= { (float)v.x, (float)v.y };		return ret;		}
static INLINE vec3_t vec3_of_dvec3(dvec3_t v)			{	vec3_t	ret	= { (float)v.x, (float)v.y, (float)v.z };		return ret;		}
static INLINE vec4_t vec4_of_dvec4(dvec4_t v)		{	vec4_t	ret	= { (float)v.x, (float)v.y, (float)v.z, (float)v.w };	return ret;		}

/* arithmetic operations */
/* int */
static INLINE ivec2_t ivec2_neg(ivec2_t v)                      {	return ivec2( -v.x, -v.y );		}
static INLINE ivec3_t ivec3_neg(ivec3_t v)                      {	return ivec3( -v.x, -v.y, -v.z );	}
static INLINE ivec4_t ivec4_neg(ivec4_t v)                      {	return ivec4( -v.x, -v.y, -v.z, -v.w );	}

static INLINE ivec2_t ivec2_add(ivec2_t a, ivec2_t b)			{	return ivec2( a.x + b.x, a.y + b.y );				}
static INLINE ivec3_t ivec3_add(ivec3_t a, ivec3_t b)			{	return ivec3( a.x + b.x, a.y + b.y, a.z + b.z );			}
static INLINE ivec4_t ivec4_add(ivec4_t a, ivec4_t b)			{	return ivec4( a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w );	}

static INLINE ivec2_t ivec2_sub(ivec2_t a, ivec2_t b)			{	return ivec2( a.x - b.x, a.y - b.y );				}
static INLINE ivec3_t ivec3_sub(ivec3_t a, ivec3_t b)			{	return ivec3( a.x - b.x, a.y - b.y, a.z - b.z );			}
static INLINE ivec4_t ivec4_sub(ivec4_t a, ivec4_t b)			{	return ivec4( a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w );	}

static INLINE ivec2_t ivec2_muli(ivec2_t a, int b)              {	return ivec2( a.x * b, a.y * b );				}
static INLINE ivec3_t ivec3_muli(ivec3_t a, int b)              {	return ivec3( a.x * b, a.y * b, a.z * b );			}
static INLINE ivec4_t ivec4_muli(ivec4_t a, int b)              {	return ivec4( a.x * b, a.y * b, a.z * b, a.w * b );		}

static INLINE ivec2_t ivec2_divi(ivec2_t a, int b)              {	return ivec2( a.x / b, a.y / b );				}
static INLINE ivec3_t ivec3_divi(ivec3_t a, int b)              {	return ivec3( a.x / b, a.y / b, a.z / b );			}
static INLINE ivec4_t ivec4_divi(ivec4_t a, int b)              {	return ivec4( a.x / b, a.y / b, a.z / b, a.w / b );		}

static INLINE ivec2_t ivec2_min(ivec2_t a, ivec2_t b)			{	return ivec2(MIN(a.x, b.x), MIN(a.y, b.y));			}
static INLINE ivec3_t ivec3_min(ivec3_t a, ivec3_t b)			{	return ivec3(MIN(a.x, b.x), MIN(a.y, b.y), MIN(a.z, b.z));	}
static INLINE ivec4_t ivec4_min(ivec4_t a, ivec4_t b)			{	return ivec4(MIN(a.x, b.x), MIN(a.y, b.y), MIN(a.z, b.z), MIN(a.w, b.w));	}
static INLINE ivec2_t ivec2_max(ivec2_t a, ivec2_t b)			{	return ivec2(MAX(a.x, b.x), MAX(a.y, b.y));			}
static INLINE ivec3_t ivec3_max(ivec3_t a, ivec3_t b)			{	return ivec3(MAX(a.x, b.x), MAX(a.y, b.y), MAX(a.z, b.z));	}
static INLINE ivec4_t ivec4_max(ivec4_t a, ivec4_t b)			{	return ivec4(MAX(a.x, b.x), MAX(a.y, b.y), MAX(a.z, b.z), MAX(a.w, b.w));	}

static INLINE bool ivec2_eq(ivec2_t a, ivec2_t b)				{	return a.x == b.x && a.y == b.y;				}
static INLINE bool ivec3_eq(ivec3_t a, ivec3_t b)				{	return a.x == b.x && a.y == b.y && a.z == b.z;			}
static INLINE bool ivec4_eq(ivec4_t a, ivec4_t b)				{	return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;	}

/* float */
static INLINE vec2_t vec2_neg(vec2_t v)					{	return vec2( -v.x, -v.y );		}
static INLINE vec3_t vec3_neg(vec3_t v)					{	return vec3( -v.x, -v.y, -v.z );	}
static INLINE vec4_t vec4_neg(vec4_t v)					{	return vec4( -v.x, -v.y, -v.z, -v.w );	}

static INLINE vec2_t vec2_add(vec2_t a, vec2_t b)			{	return vec2( a.x + b.x, a.y + b.y );				}
static INLINE vec3_t vec3_add(vec3_t a, vec3_t b)			{	return vec3( a.x + b.x, a.y + b.y, a.z + b.z );			}
static INLINE vec4_t vec4_add(vec4_t a, vec4_t b)			{	return vec4( a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w );	}

static INLINE vec2_t vec2_sub(vec2_t a, vec2_t b)			{	return vec2( a.x - b.x, a.y - b.y );				}
static INLINE vec3_t vec3_sub(vec3_t a, vec3_t b)			{	return vec3( a.x - b.x, a.y - b.y, a.z - b.z );			}
static INLINE vec4_t vec4_sub(vec4_t a, vec4_t b)			{	return vec4( a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w );	}

static INLINE vec2_t vec2_mulf(vec2_t a, float b)			{	return vec2( a.x * b, a.y * b );				}
static INLINE vec3_t vec3_mulf(vec3_t a, float b)			{	return vec3( a.x * b, a.y * b, a.z * b );			}
static INLINE vec4_t vec4_mulf(vec4_t a, float b)			{	return vec4( a.x * b, a.y * b, a.z * b, a.w * b );		}

static INLINE vec2_t vec2_divf(vec2_t a, float b)			{	return vec2( a.x / b, a.y / b );				}
static INLINE vec3_t vec3_divf(vec3_t a, float b)			{	return vec3( a.x / b, a.y / b, a.z / b );			}
static INLINE vec4_t vec4_divf(vec4_t a, float b)			{	return vec4( a.x / b, a.y / b, a.z / b, a.w / b );		}

static INLINE vec2_t vec2_min(vec2_t a, vec2_t b)			{	return vec2(MIN(a.x, b.x), MIN(a.y, b.y));			}
static INLINE vec3_t vec3_min(vec3_t a, vec3_t b)			{	return vec3(MIN(a.x, b.x), MIN(a.y, b.y), MIN(a.z, b.z));	}
static INLINE vec4_t vec4_min(vec4_t a, vec4_t b)			{	return vec4(MIN(a.x, b.x), MIN(a.y, b.y), MIN(a.z, b.z), MIN(a.w, b.w));	}
static INLINE vec2_t vec2_max(vec2_t a, vec2_t b)			{	return vec2(MAX(a.x, b.x), MAX(a.y, b.y));			}
static INLINE vec3_t vec3_max(vec3_t a, vec3_t b)			{	return vec3(MAX(a.x, b.x), MAX(a.y, b.y), MAX(a.z, b.z));	}
static INLINE vec4_t vec4_max(vec4_t a, vec4_t b)			{	return vec4(MAX(a.x, b.x), MAX(a.y, b.y), MAX(a.z, b.z), MAX(a.w, b.w));	}

static INLINE bool vec2_eq(vec2_t a, vec2_t b)				{	return a.x == b.x && a.y == b.y;				}
static INLINE bool vec3_eq(vec3_t a, vec3_t b)				{	return a.x == b.x && a.y == b.y && a.z == b.z;			}
static INLINE bool vec4_eq(vec4_t a, vec4_t b)				{	return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;	}

static INLINE vec2_t vec3_xy(vec3_t v)                      { return vec2(v.x, v.y); }
static INLINE vec2_t vec3_yz(vec3_t v)                      { return vec2(v.y, v.z); }
static INLINE vec2_t vec3_xz(vec3_t v)                      { return vec2(v.x, v.z); }

static INLINE vec2_t vec3_yx(vec3_t v)                      { return vec2(v.y, v.x); }
static INLINE vec2_t vec3_zy(vec3_t v)                      { return vec2(v.z, v.y); }
static INLINE vec2_t vec3_zx(vec3_t v)                      { return vec2(v.z, v.x); }
/* double */
static INLINE dvec2_t dvec2_neg(dvec2_t v)					{	return dvec2( -v.x, -v.y );		}
static INLINE dvec3_t dvec3_neg(dvec3_t v)					{	return dvec3( -v.x, -v.y, -v.z );	}
static INLINE dvec4_t dvec4_neg(dvec4_t v)					{	return dvec4( -v.x, -v.y, -v.z, -v.w );	}

static INLINE dvec2_t dvec2_add(dvec2_t a, dvec2_t b)			{	return dvec2( a.x + b.x, a.y + b.y );				}
static INLINE dvec3_t dvec3_add(dvec3_t a, dvec3_t b)			{	return dvec3( a.x + b.x, a.y + b.y, a.z + b.z );			}
static INLINE dvec4_t dvec4_add(dvec4_t a, dvec4_t b)			{	return dvec4( a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w );	}

static INLINE dvec2_t dvec2_sub(dvec2_t a, dvec2_t b)			{	return dvec2( a.x - b.x, a.y - b.y );				}
static INLINE dvec3_t dvec3_sub(dvec3_t a, dvec3_t b)			{	return dvec3( a.x - b.x, a.y - b.y, a.z - b.z );			}
static INLINE dvec4_t dvec4_sub(dvec4_t a, dvec4_t b)			{	return dvec4( a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w );	}

static INLINE dvec2_t dvec2_mulf(dvec2_t a, double b)			{	return dvec2( a.x * b, a.y * b );				}
static INLINE dvec3_t dvec3_mulf(dvec3_t a, double b)			{	return dvec3( a.x * b, a.y * b, a.z * b );			}
static INLINE dvec4_t dvec4_mulf(dvec4_t a, double b)			{	return dvec4( a.x * b, a.y * b, a.z * b, a.w * b );		}

static INLINE dvec2_t dvec2_divf(dvec2_t a, double b)			{	return dvec2( a.x / b, a.y / b );				}
static INLINE dvec3_t dvec3_divf(dvec3_t a, double b)			{	return dvec3( a.x / b, a.y / b, a.z / b );			}
static INLINE dvec4_t dvec4_divf(dvec4_t a, double b)			{	return dvec4( a.x / b, a.y / b, a.z / b, a.w / b );		}

static INLINE dvec2_t dvec2_min(dvec2_t a, dvec2_t b)			{	return dvec2(MIN(a.x, b.x), MIN(a.y, b.y));			}
static INLINE dvec3_t dvec3_min(dvec3_t a, dvec3_t b)			{	return dvec3(MIN(a.x, b.x), MIN(a.y, b.y), MIN(a.z, b.z));	}
static INLINE dvec4_t dvec4_min(dvec4_t a, dvec4_t b)			{	return dvec4(MIN(a.x, b.x), MIN(a.y, b.y), MIN(a.z, b.z), MIN(a.w, b.w));	}
static INLINE dvec2_t dvec2_max(dvec2_t a, dvec2_t b)			{	return dvec2(MAX(a.x, b.x), MAX(a.y, b.y));			}
static INLINE dvec3_t dvec3_max(dvec3_t a, dvec3_t b)			{	return dvec3(MAX(a.x, b.x), MAX(a.y, b.y), MAX(a.z, b.z));	}
static INLINE dvec4_t dvec4_max(dvec4_t a, dvec4_t b)			{	return dvec4(MAX(a.x, b.x), MAX(a.y, b.y), MAX(a.z, b.z), MAX(a.w, b.w));	}

static INLINE bool dvec2_eq(dvec2_t a, dvec2_t b)				{	return a.x == b.x && a.y == b.y;				}
static INLINE bool dvec3_eq(dvec3_t a, dvec3_t b)				{	return a.x == b.x && a.y == b.y && a.z == b.z;			}
static INLINE bool dvec4_eq(dvec4_t a, dvec4_t b)				{	return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;	}

/* geometric operations */
static INLINE float vec2_dot(vec2_t a, vec2_t b)			{	return (a.x * b.x) + (a.y * b.y);				}
static INLINE float vec3_dot(vec3_t a, vec3_t b)			{	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);			}
static INLINE float vec4_dot(vec4_t a, vec4_t b)			{	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);	}

static INLINE vec3_t vec3_cross(vec3_t a, vec3_t b)			{	return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);	}

static INLINE float vec2_length(vec2_t v)				{	return sqrtf(vec2_dot(v, v));					}
static INLINE float vec3_length(vec3_t v)				{	return sqrtf(vec3_dot(v, v));					}
static INLINE float vec4_length(vec4_t v)				{	return sqrtf(vec4_dot(v, v));					}

static INLINE float vec2_distance(vec2_t v0, vec2_t v1)			{	vec2_t	s = vec2_sub(v1, v0); return vec2_length(s);		}
static INLINE float vec3_distance(vec3_t v0, vec3_t v1)			{	vec3_t	s = vec3_sub(v1, v0); return vec3_length(s);		}
static INLINE float vec4_distance(vec4_t v0, vec4_t v1)			{	vec4_t	s = vec4_sub(v1, v0); return vec4_length(s);		}

static INLINE vec2_t vec2_normalize(vec2_t v)				{	float len = vec2_length(v); return vec2_divf(v, len);		}
static INLINE vec3_t vec3_normalize(vec3_t v)				{	float len = vec3_length(v); return vec3_divf(v, len);		}
static INLINE vec4_t vec4_normalize(vec4_t v)				{	float len = vec4_length(v); return vec4_divf(v, len);		}

/* double */
static INLINE double dvec2_dot(dvec2_t a, dvec2_t b)			{	return (a.x * b.x) + (a.y * b.y);				}
static INLINE double dvec3_dot(dvec3_t a, dvec3_t b)			{	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);			}
static INLINE double dvec4_dot(dvec4_t a, dvec4_t b)			{	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);	}

static INLINE dvec3_t dvec3_cross(dvec3_t a, dvec3_t b)			{	return dvec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);	}

static INLINE double dvec2_length(dvec2_t v)				{	return sqrt(dvec2_dot(v, v));					}
static INLINE double dvec3_length(dvec3_t v)				{	return sqrt(dvec3_dot(v, v));					}
static INLINE double dvec4_length(dvec4_t v)				{	return sqrt(dvec4_dot(v, v));					}

static INLINE double dvec2_distance(dvec2_t v0, dvec2_t v1)			{	dvec2_t	s = dvec2_sub(v1, v0); return dvec2_length(s);		}
static INLINE double dvec3_distance(dvec3_t v0, dvec3_t v1)			{	dvec3_t	s = dvec3_sub(v1, v0); return dvec3_length(s);		}
static INLINE double dvec4_distance(dvec4_t v0, dvec4_t v1)			{	dvec4_t	s = dvec4_sub(v1, v0); return dvec4_length(s);		}

static INLINE dvec2_t dvec2_normalize(dvec2_t v)				{	double len = dvec2_length(v); return dvec2_divf(v, len);		}
static INLINE dvec3_t dvec3_normalize(dvec3_t v)				{	double len = dvec3_length(v); return dvec3_divf(v, len);		}
static INLINE dvec4_t dvec4_normalize(dvec4_t v)				{	double len = dvec4_length(v); return dvec4_divf(v, len);		}

/*******************************************************************************
** matrices
*******************************************************************************/
/*
** matX_t structure
** The matrix is layed out as the following:
**        | m0 mN   ... |   | v[0].x v[1].x ... |
**   M =  | m1 mN+1 ... | = | v[0].y v[1].y ... |
**        | .. ..   ... |   | ...    ...    ... |
*/
typedef union {
    float	m[2][2];
    vec2_t	col[2];
} mat2_t;

typedef union {
    float	m[3][3];
    vec3_t	col[3];
} mat3_t;

typedef union {
    float	m[4][4];
    vec4_t	col[4];
} mat4_t;

static INLINE mat2_t mat2(float m0, float m1,
                          float m2, float m3)				{	mat2_t	m = {{ {m0, m1}, {m2, m3} }}; return m;			}

static INLINE mat3_t mat3(float m0, float m1, float m2,
                          float m3, float m4, float m5,
                          float m6, float m7, float m8)			{	mat3_t	m = {{ {m0, m1, m2}, {m3, m4, m5}, {m6, m7, m8} }}; return m;		}

static INLINE mat4_t mat4(float m0, float m1, float m2, float m3,
                          float m4, float m5, float m6, float m7,
                          float m8, float m9, float m10, float m11,
                          float m12, float m13, float m14, float m15)	{	mat4_t	m = {{ {m0, m1, m2, m3}, {m4, m5, m6, m7}, {m8, m9, m10, m11}, {m12, m13, m14, m15} }}; return m;		}


static INLINE mat2_t mat2_identity()				{	return mat2(1.0f, 0.0f,
                                                                    0.0f, 1.0f);		}
static INLINE mat3_t mat3_identity()				{	return mat3(1.0f, 0.0f, 0.0f,
                                                                    0.0f, 1.0f, 0.0f,
                                                                    0.0f, 0.0f, 1.0f);		}

static INLINE mat4_t mat4_identity()				{	return mat4(1.0f, 0.0f, 0.0f, 0.0f,
                                                                    0.0f, 1.0f, 0.0f, 0.0f,
                                                                    0.0f, 0.0f, 1.0f, 0.0f,
                                                                    0.0f, 0.0f, 0.0f, 1.0f);	}

static INLINE vec2_t mat2_row(mat2_t m, unsigned int idx)	{	return vec2(m.m[0][idx], m.m[1][idx]);				}
static INLINE vec3_t mat3_row(mat3_t m, unsigned int idx)	{	return vec3(m.m[0][idx], m.m[1][idx], m.m[2][idx]);			}
static INLINE vec4_t mat4_row(mat4_t m, unsigned int idx)	{	return vec4(m.m[0][idx], m.m[1][idx], m.m[2][idx], m.m[3][idx]);	}

DLL_3DMATH_PUBLIC mat2_t mat2_mulm(mat2_t a, mat2_t b);
DLL_3DMATH_PUBLIC mat3_t mat3_mulm(mat3_t a, mat3_t b);
DLL_3DMATH_PUBLIC mat4_t mat4_mulm(mat4_t a, mat4_t b);

DLL_3DMATH_PUBLIC mat2_t mat2_mulf(mat2_t a, float b);
DLL_3DMATH_PUBLIC mat3_t mat3_mulf(mat3_t a, float b);
DLL_3DMATH_PUBLIC mat4_t mat4_mulf(mat4_t a, float b);

DLL_3DMATH_PUBLIC mat2_t mat2_inverse(mat2_t m);
DLL_3DMATH_PUBLIC mat3_t mat3_inverse(mat3_t m);
DLL_3DMATH_PUBLIC mat4_t mat4_inverse(mat4_t m);

DLL_3DMATH_PUBLIC mat2_t mat2_transpose(mat2_t m);
DLL_3DMATH_PUBLIC mat3_t mat3_transpose(mat3_t m);
DLL_3DMATH_PUBLIC mat4_t mat4_transpose(mat4_t m);

DLL_3DMATH_PUBLIC float mat2_determinant(mat2_t m);
DLL_3DMATH_PUBLIC float mat3_determinant(mat3_t m);
DLL_3DMATH_PUBLIC float mat4_determinant(mat4_t m);

/* v' = m * v */
static INLINE vec2_t mat2_mul_vec2(mat2_t m, vec2_t v) {
    vec2_t	r0	= mat2_row(m, 0);
    vec2_t	r1	= mat2_row(m, 1);
    return vec2(vec2_dot(v, r0), vec2_dot(v, r1));
}

static INLINE vec3_t mat3_mul_vec3(mat3_t m, vec3_t v) {
    vec3_t	r0	= mat3_row(m, 0);
    vec3_t	r1	= mat3_row(m, 1);
    vec3_t	r2	= mat3_row(m, 2);
    return vec3(vec3_dot(v, r0), vec3_dot(v, r1), vec3_dot(v, r2));
}

static INLINE vec4_t mat4_mul_vec4(mat4_t m, vec4_t v) {
    vec4_t	r0	= mat4_row(m, 0);
    vec4_t	r1	= mat4_row(m, 1);
    vec4_t	r2	= mat4_row(m, 2);
    vec4_t	r3	= mat4_row(m, 3);

    return vec4(vec4_dot(v, r0), vec4_dot(v, r1), vec4_dot(v, r2), vec4_dot(v, r3));
}

/* v' = v * m */
static INLINE vec2_t    vec2_mul_mat2(vec2_t v, mat2_t m)           {	return vec2(vec2_dot(v, m.col[0]), vec2_dot(v, m.col[1]));	}
static INLINE vec3_t    vec3_mul_mat3(vec3_t v, mat3_t m)           {	return vec3(vec3_dot(v, m.col[0]), vec3_dot(v, m.col[1]), vec3_dot(v, m.col[2]));	}
static INLINE vec4_t    vec4_mul_mat4(vec4_t v, mat4_t m)           {	return vec4(vec4_dot(v, m.col[0]), vec4_dot(v, m.col[1]), vec4_dot(v, m.col[2]), vec4_dot(v, m.col[3]));	}

/*******************************************************************************
** quaternion
*******************************************************************************/
typedef struct {
    float	x, y, z, w;
} quat_t;

static INLINE quat_t        quat(float x, float y, float z, float w){ quat_t r = { x, y, z, w }; return r;	}
static INLINE quat_t        quat_neg(quat_t q)                      { quat_t r = { -q.x, -q.y, -q.z, -q.w }; return r;	}
static INLINE quat_t        quat_add(quat_t q0, quat_t q1)          { quat_t r = { q0.x + q1.x, q0.y + q1.y, q0.z + q1.z, q0.w + q1.w }; return r;	}
static INLINE quat_t        quat_addf(quat_t q0, float q1)          { quat_t r = { q0.x + q1, q0.y + q1, q0.z + q1, q0.w + q1 }; return r;	}
static INLINE quat_t        quat_sub(quat_t q0, quat_t q1)          { quat_t r = { q0.x - q1.x, q0.y - q1.y, q0.z - q1.z, q0.w - q1.w }; return r;	}
static INLINE quat_t        quat_subf(quat_t q0, float q1)          { quat_t r = { q0.x - q1, q0.y - q1, q0.z - q1, q0.w - q1 }; return r;	}
static INLINE quat_t        quat_fsub(float q0, quat_t q1)          { quat_t r = { q0 - q1.x, q0 - q1.y, q0 - q1.z, q0 - q1.w }; return r;	}
static INLINE quat_t        quat_mulf(quat_t q0, float q1)          { quat_t r = { q0.x * q1, q0.y * q1, q0.z * q1, q0.w * q1 }; return r;	}
static INLINE quat_t        quat_fmul(float q0, quat_t q1)          { quat_t r = { q0 * q1.x, q0 * q1.y, q0 * q1.z, q0 * q1.w }; return r;	}
static INLINE quat_t        quat_divf(quat_t q0, float q1)          { quat_t r = { q0.x / q1, q0.y / q1, q0.z / q1, q0.w / q1 }; return r;	}
static INLINE quat_t        quat_fdiv(float q0, quat_t q1)          { quat_t r = { q0 / q1.x, q0 / q1.y, q0 / q1.z, q0 / q1.w }; return r;	}
static INLINE bool          quat_eq(quat_t q0, quat_t q1)           { return (q0.x == q1.x && q0.y == q1.y && q0.z == q1.z && q0.w == q1.w);	}
static INLINE bool          quat_neq(quat_t q0, quat_t q1)          { return !quat_eq(q0, q1); }

static INLINE float         quat_dot(quat_t q0, quat_t q1)          { return q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w;	}
static INLINE float         quat_length(quat_t q)                   { return sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);	}
static INLINE quat_t		quat_conjugate(quat_t q)                { return quat(-q.x, -q.y, -q.z, q.w);	}
static INLINE quat_t		quat_normalize(quat_t q)                { return (quat_length(q) > 0 ) ? quat_divf(q, quat_length(q)) : q;	}
static INLINE quat_t		quat_inverse(quat_t q)                  { return quat_normalize(quat_conjugate(q));	}

static INLINE quat_t
quat_mul(quat_t q0, quat_t q1)	{
    float	x = q0.w * q1.x + q0.x * q1.w + q0.y * q1.z - q0.z * q1.y;
    float	y = q0.w * q1.y + q0.y * q1.w + q0.z * q1.x - q0.x * q1.z;
    float	z = q0.w * q1.z + q0.z * q1.w + q0.x * q1.y - q0.y * q1.x;
    float	w = q0.w * q1.w - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z;
    return quat_normalize(quat(x, y, z, w));
}


DLL_3DMATH_PUBLIC mat3_t			mat3_from_quat(quat_t q);
DLL_3DMATH_PUBLIC mat4_t			mat4_from_quat(quat_t q);
DLL_3DMATH_PUBLIC void				quat_to_axis_angle(quat_t q, vec3_t *axis, float* angle);
DLL_3DMATH_PUBLIC quat_t			quat_from_mat3(mat3_t m);
DLL_3DMATH_PUBLIC quat_t			quat_from_mat4(mat4_t m);
DLL_3DMATH_PUBLIC quat_t			quat_from_axis_angle(vec3_t axis, float angle);

/*******************************************************************************
**
** geometric primitives
**
*******************************************************************************/

/*******************************************************************************
**  rect
*******************************************************************************/
typedef struct {
    float		x, y;
    float		width, height;
} rect_t;

static INLINE rect_t		rect(float x, float y, float width, float height)	{ rect_t	r = { x, y, width, height }; return r;	}

static INLINE rect_t		rect_from_vec2(vec2_t mn, vec2_t mx) {
    float		min_x	= MIN(mn.x, mx.x);
    float		min_y	= MIN(mn.y, mx.y);
    float		max_x	= MAX(mn.x, mx.x);
    float		max_y	= MAX(mn.y, mx.y);
    rect_t		r = { min_x, min_y, max_x - min_x, max_y - min_y };
    return r;
}

static INLINE vec2_t		rect_min(rect_t r)					{ vec2_t	v = { r.x, r.y }; return v;	}
static INLINE vec2_t		rect_max(rect_t r)					{ vec2_t	v = { r.x + r.width, r.y + r.height}; return v;	}

static INLINE rect_t		rect_intersect(rect_t r0, rect_t r1) {
    vec2_t	min	= vec2_max(rect_min(r0), rect_min(r1));
    vec2_t	max	= vec2_min(rect_max(r0), rect_max(r1));
    return rect_from_vec2(min, max);
}

typedef struct {
    int         x, y;
    int         width, height;
} irect_t;

static INLINE irect_t		irect(int x, int y, int width, int height)  {   irect_t r = { x, y, width, height }; return r;	}

static INLINE irect_t		irect_from_vec2(ivec2_t mn, ivec2_t mx) {
    int         min_x   = MIN(mn.x, mx.x);
    int         min_y   = MIN(mn.y, mx.y);
    int         max_x   = MAX(mn.x, mx.x);
    int         max_y   = MAX(mn.y, mx.y);
    irect_t		r = { min_x, min_y, max_x - min_x, max_y - min_y };
    return r;
}

static INLINE ivec2_t       irect_min(irect_t r)					{ ivec2_t	v = { r.x, r.y }; return v;	}
static INLINE ivec2_t       irect_max(irect_t r)					{ ivec2_t	v = { r.x + r.width, r.y + r.height}; return v;	}

static INLINE irect_t       irect_intersect(irect_t r0, irect_t r1) {
    ivec2_t	min	= ivec2_max(irect_min(r0), irect_min(r1));
    ivec2_t	max	= ivec2_min(irect_max(r0), irect_max(r1));
    return irect_from_vec2(min, max);
}

/*******************************************************************************
**  box3
*******************************************************************************/
typedef struct {
    vec3_t		center;
    vec3_t		extent;
} box3_t;

static INLINE box3_t		box3(vec3_t center, vec3_t extent)	{ box3_t b; b.center = center; b.extent = extent; return b; }
static INLINE vec3_t		box3_get_min(box3_t b)			{ return vec3_sub(b.center, b.extent); }
static INLINE vec3_t		box3_get_max(box3_t b)			{ return vec3_add(b.center, b.extent); }

static INLINE box3_t
box3_from_min_max(vec3_t min, vec3_t max) {
    box3_t res;
    res.center = vec3_mulf(vec3_add(min, max), 0.5f);
    res.extent = vec3_sub(max, res.center);
    return res;
}

static INLINE box3_t
box3_intersect(box3_t a, box3_t b) {
    vec3_t	min_a	= box3_get_min(a);
    vec3_t	max_a	= box3_get_max(a);
    vec3_t	min_b	= box3_get_min(b);
    vec3_t	max_b	= box3_get_max(b);

    vec3_t	min_r	= vec3_max(min_a, min_b);
    vec3_t	max_r	= vec3_min(max_a, max_b);

    return box3_from_min_max(min_r, max_r);
}

/*******************************************************************************
** ray3
*******************************************************************************/
typedef struct {
    vec3_t			start;
    vec3_t			direction;
} ray3_t;

static INLINE ray3_t		ray3_from(vec3_t start, vec3_t direction)	{	ray3_t r; r.start = start; r.direction = direction; return r; }

/*!
 @brief get point at parametric distance
 @return the point at parametric distance
*/
static INLINE vec3_t		ray3_at(ray3_t r, float t)			{	return vec3_add(vec3_mulf(r.direction, t), r.start);	}

/*!
 @brief normalize the ray direction
*/
static INLINE ray3_t		ray3_normalize(ray3_t r)			{	ray3_t ret; ret.start = r.start; r.direction = vec3_normalize(r.direction);	return ret;	}

/*******************************************************************************
**  plane
*******************************************************************************/
typedef struct {
    float			a, b, c, d;
} plane_t;

static INLINE plane_t       plane(float a, float b, float c, float d){	plane_t p = { a, b, c, d }; return p;		}
static INLINE plane_t       plane_from(vec3_t n, float c)           {	plane_t p = { n.x, n.y, n.z, c }; return p;	}
static INLINE vec3_t        plane_normal(plane_t p)                 {	return vec3(p.a, p.b, p.c);			}
static INLINE float         plane_constant(plane_t p)               {	return p.d;					}


/*!
 @brief normalize the plane
 @param p the plane to normalize
 @return normalized plane
*/
static INLINE
plane_t
plane_normalize(plane_t p) {
    float		l	= vec3_length(plane_normal(p));
    return plane_from(vec3_divf(plane_normal(p), l), p.d * l);
}

/*******************************************************************************
**  tri3
*******************************************************************************/
/*! @brief get the normal of the triange */
static INLINE
vec3_t
tri3_normal(vec3_t v0, vec3_t v1, vec3_t v2) {
    vec3_t v10 = vec3_sub(v1, v0);
    vec3_t v20 = vec3_sub(v2, v0);
    return vec3_normalize(vec3_cross(v10, v20));
}

/*! @brief plane from triangle */
static INLINE plane_t
tri3_plane(vec3_t v0, vec3_t v1, vec3_t v2) {
    vec3_t  n   = tri3_normal(v0, v1, v2);
    float   d   = -vec3_dot(n, v0);
    return plane_from(n, d);
}

/*******************************************************************************
**
** queries
**
*******************************************************************************/
DLL_3DMATH_PUBLIC bool              plane_ray3_intersection(plane_t p, ray3_t r, vec3_t* out);

/*! @brief compute barycentric coordinate of a point v */
DLL_3DMATH_PUBLIC vec3_t            tri3_point_of_barycentric_coordinates(vec3_t v0, vec3_t v1, vec3_t v2, vec3_t p);
DLL_3DMATH_PUBLIC vec3_t            tri3_get_point_barycentric_coordinates(vec3_t v0, vec3_t v1, vec3_t v2, vec3_t p);
DLL_3DMATH_PUBLIC vec2_t            tri2_point_of_barycentric_coordinates(vec2_t v0, vec2_t v1, vec2_t v2, vec2_t p);
DLL_3DMATH_PUBLIC vec2_t            tri2_get_point_barycentric_coordinates(vec2_t v0, vec2_t v1, vec2_t v2, vec2_t p);

DLL_3DMATH_PUBLIC bool              ray3_tri3_intersection(ray3_t r, vec3_t v1, vec3_t v2, vec3_t v3, vec3_t* out);

DLL_3DMATH_PUBLIC vec2_t            closest_on_segment2(vec2_t seg_start, vec2_t seg_end, vec2_t pt);
DLL_3DMATH_PUBLIC vec3_t            closest_on_segment3(vec3_t seg_start, vec3_t seg_end, vec3_t pt);
DLL_3DMATH_PUBLIC float             distance_to_segment2(vec2_t seg_start, vec2_t seg_end, vec2_t pt);
DLL_3DMATH_PUBLIC float             distance_to_segment3(vec3_t seg_start, vec3_t seg_end, vec3_t pt);

DLL_3DMATH_PUBLIC float             distance_to_plane(plane_t p, vec3_t pt);
DLL_3DMATH_PUBLIC vec3_t            project_to_plane(plane_t p, vec3_t pt);


/*******************************************************************************
**
** transforms
**
*******************************************************************************/

/** @name orthogonal 2d projection matrix
 @{ */
DLL_3DMATH_PUBLIC mat4_t			mat4_ortho (float left, float right, float bottom, float top);
DLL_3DMATH_PUBLIC mat4_t			mat4_ortho2(vec2_t lb, vec2_t rt);
/* @} */

/** @name orthogonal 3d projection matrix
 @{ */
DLL_3DMATH_PUBLIC mat4_t			mat4_ortho3(vec3_t lbn, vec3_t rtf);
DLL_3DMATH_PUBLIC mat4_t			mat4_ortho4(float left, float right, float bottom, float top, float near, float far);

/* @} */

/**
 perspective projection matrix
 @param fovy field of view in radians and in y direction
 @param aspect the aspect ratio
 @param near near plane value
 @param far far plane value
*/
DLL_3DMATH_PUBLIC mat4_t			mat4_perspective(float fovy, float aspect, float near, float far);

/** translation matrix */
DLL_3DMATH_PUBLIC mat4_t			mat4_translation(vec3_t trans);

/** scale matrix */
DLL_3DMATH_PUBLIC mat4_t			mat4_scale(vec3_t scale);

/** @name rotation matrix
 @{ */
DLL_3DMATH_PUBLIC mat4_t			mat4_rotation(quat_t q);
DLL_3DMATH_PUBLIC mat4_t			mat4_rotation2(float angle, vec3_t axis);
/* @} */

/**
 lookat matrix
 @param eye the eye position
 @param dest the eye destination position
 @param up the up vector
 @return the lookat matrix
*/
DLL_3DMATH_PUBLIC mat4_t			mat4_lookat(vec3_t eye, vec3_t dest, vec3_t up);

/**
 frustum matrix
 @param lbn left/bottom/near
 @param rtf right/top/far
 @return the frustum matrix
 @note both near and far must be positive (the function will compute the frustum regardless even if it is not valid)
*/
DLL_3DMATH_PUBLIC mat4_t			mat4_frustum(vec3_t lbn, vec3_t rtf);

/**
 project a point to the screen
 @param world world matrix (or modelview matrix)
 @param persp perspective matrix
 @param lb view left/bottom
 @param rt view right/top
 @param pt the input point
 @return the projected point
*/
DLL_3DMATH_PUBLIC vec3_t			vec3_project(mat4_t world, mat4_t persp, vec2_t lb, vec2_t rt, vec3_t pt);

/**
 unproject a point to the 3d system
 @param world world matrix (or modelview matrix)
 @param persp perspective matrix
 @param lb view left/bottom
 @param rt view right/top
 @param pt the input point
 @return the unprojected point
*/
DLL_3DMATH_PUBLIC vec3_t			vec3_unproject(mat4_t world, mat4_t persp, vec2_t lb, vec2_t rt, vec3_t pt);

/**
 @brief convert from world coordinates to local coordinates
 @param m world matrix
 @param in the input world coordinates
 @return local coordinates
*/
DLL_3DMATH_PUBLIC vec3_t			world3_to_local3(mat4_t world, vec3_t in);

/*
** vector transform:
**
** | m0  mN   ... |   | x |   | x'|
** | m1  mN+1 ... | * | y | = | y'|
** | ... ...  ... |   |...|   |...|
*/

/**
 @brief transform a vec3 by a mat4
 @param m matrix
 @param in input vector
 @return the transformed vector
 @note this will divide xyz by w
*/
DLL_3DMATH_PUBLIC vec3_t			transform_vec3(mat4_t m, vec3_t in);

/**
 @brief transform a vec4 by a mat4
 @param m matrix
 @param in input vector
 @return the transformed vector
*/
DLL_3DMATH_PUBLIC vec4_t			transform_vec4(mat4_t m, vec4_t in);

/**
 * decompose a matrix into scale, rotation and translation
 */
DLL_3DMATH_PUBLIC bool				mat4_decompose(mat4_t m, vec3_t *scale, quat_t *rot, vec3_t *trans);

#ifdef __cplusplus
}
#endif

#endif // _3DMATH_H
