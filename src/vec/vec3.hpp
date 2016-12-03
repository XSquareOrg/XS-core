/* ------------------------------------------------------------------------ *
 *   XSquare is free software: you can redistribute it and/or               *
 *   modify it under the terms of the GNU Lesser General Public License as  *
 *   published by the Free Software Foundation version 3 of the Licence, or *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   XSquare is distributed in the hope that it will be useful,             *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 *   General Public License for more details.                               *
 *                                                                          *
 *   You should have received copies of the GNU General Public License and  *
 *   the GNU Lesser General Public License along with this program.  If     *
 *   not, see http://www.gnu.org/licenses/.                                 *
* ------------------------------------------------------------------------- */


#ifndef XS_CORE_VEC3__
#define XS_CORE_VEC3__


#include "../simd/mm3.hpp"

namespace xs_core {

class Vec3i;
class Vec3f;

template <class NUM, class T>
class _V3Base {
// Mixin to provide funcs common to Vec3f and Vec3i
public:
};


class Vec3f: public _V3Base<Vec3f, float>, public mm3f<Vec3f> {
public:
    operator Vec3i();
    operator const Vec3i();
    Vec3f abs(void);
    Vec3f operator-() { // negation
        this->u.data.a[0] = -this->u.data.a[0];
        this->u.data.a[1] = -this->u.data.a[1];
        this->u.data.a[2] = -this->u.data.a[2];
        return *this;
    }
    float distance(const Vec3f v) {
        float3u u;
        __m128 m = _mm_sub_ps(this->u.data.v, v.u.data.v);
        m = _mm_mul_ps(m, m);
        u.data.v = m;
        return sqrt(u.hadd()); // return sqrt(_hadd4f(m));
    }
};


class Vec3i: public _V3Base<Vec3i, int>, public mm3i<Vec3i> {
public:
    operator Vec3i();
    operator const Vec3i();
    Vec3i abs(void);
    Vec3i operator-() { // negation
        this->u.data.a[0] = -this->u.data.a[0];
        this->u.data.a[1] = -this->u.data.a[1];
        this->u.data.a[2] = -this->u.data.a[2];
        return *this;
    }
    int distance(const Vec3i v) {
        int3u u;
        __m128i m = _mm_sub_epi32(this->u.data.v, v.u.data.v);
        // m = _mm_mul_epi32(m, m);
        // FIXME error _mm_mul_epi32 was not declared in this scope
        u.data.v = m;
        // workaround for _mm_mul_epi32 -- multiply each axis individually
        u.data.a[0] *= u.data.a[0];
        u.data.a[1] *= u.data.a[1];
        u.data.a[2] *= u.data.a[2];
        return sqrt(u.hadd()); // return sqrt(_hadd4i(m));
    }
};


} // xs_core
#endif // XS_CORE_Vec3__
