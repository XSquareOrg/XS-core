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


#ifndef XS_CORE_VEC4__
#define XS_CORE_VEC4__


#include "../simd/mm4.hpp"

namespace xs_core {

class Vec4i;
class Vec4f;

template <class NUM, class T>
class _V4Base {
// Mixin to provide funcs common to Vec4f and Vec4i
public:
};


class Vec4f: public _V4Base<Vec4f, float>, public mm4f<Vec4f> {
public:
    operator Vec4i();
    operator const Vec4i();
    Vec4f abs(void);
    Vec4f operator-() { // negation
        this->u.data.a[0] = -this->u.data.a[0];
        this->u.data.a[1] = -this->u.data.a[1];
        this->u.data.a[2] = -this->u.data.a[2];
        this->u.data.a[3] = -this->u.data.a[3];
        return *this;
    }
    float distance(const Vec4f v) {
        float4u u;
        __m128 m = _mm_sub_ps(this->u.data.v, v.u.data.v);
        m = _mm_mul_ps(m, m);
        u.data.v = m;
        return sqrt(u.hadd()); // return sqrt(_hadd4f(m));
    }
    Vec4f operator+=(const Vec4f v) {
        __m128 m = _mm_add_ps(this->u.data.v, v.u.data.v);
        u.data.v = m;
        return *this;
    }
    Vec4f operator-=(const Vec4f v) {
        __m128 m = _mm_sub_ps(this->u.data.v, v.u.data.v);
        u.data.v = m;
        return *this;
    }
    Vec4f operator*=(const Vec4f v) {
        __m128 m = _mm_mul_ps(this->u.data.v, v.u.data.v);
        u.data.v = m;
        return *this;
    }
};


class Vec4i: public _V4Base<Vec4i, int>, public mm4i<Vec4i> {
public:
    operator Vec4i();
    operator const Vec4i();
    Vec4i abs(void);
    Vec4i operator-() { // negation
        this->u.data.a[0] = -this->u.data.a[0];
        this->u.data.a[1] = -this->u.data.a[1];
        this->u.data.a[2] = -this->u.data.a[2];
        this->u.data.a[3] = -this->u.data.a[3];
        return *this;
    }
    int distance(const Vec4i v) {
        int4u u;
        __m128i m = _mm_sub_epi32(this->u.data.v, v.u.data.v);
        // m = _mm_mul_epi32(m, m);
        // FIXME error _mm_mul_epi32 was not declared in this scope
        u.data.v = m;
        return sqrt(u.hadd()); // return sqrt(_hadd4i(m));
    }
    Vec4i operator+=(const Vec4i v) {
        __m128i m = _mm_add_epi32(this->u.data.v, v.u.data.v);
        u.data.v = m;
        return *this;
    }
    Vec4i operator-=(const Vec4i v) {
        __m128i m = _mm_sub_epi32(this->u.data.v, v.u.data.v);
        u.data.v = m;
        return *this;
    }

};


} // xs_core
#endif // XS_CORE_VEC4__
