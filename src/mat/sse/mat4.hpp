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


#ifndef XS_CORE_MAT4_SSE__
#define XS_CORE_MAT4_SSE__

// SSE* version
#include "../../simd/simd_include.hpp"

namespace xs_core {


template <class MM, typename NUM>
class mat4u {
public:
    union {NUM a[4]; MM v;} x; // abcd
    union {NUM a[4]; MM v;} y; // efgh
    union {NUM a[4]; MM v;} z; // ijkl
    union {NUM a[4]; MM v;} w; // mnop
    const unsigned width = 4;
    const unsigned height = 4;
};


template <class U, typename NUM, class T>
class Mat4Base {
    U u;
public:
    const unsigned width(void) {return 4;}
    const unsigned height(void) {return 4;}
    bool is_square(void) {return true;}
    inline T operator+(const T& rhs) {
        T t;
        t.u.data.v += rhs.u.data.v;
        return t;
    }
    inline T operator-(const T& rhs) {
        T t;
        t.u.data.v -= rhs.u.data.v;
        return t;
    }
    inline T operator*(const NUM rhs) { // scalar product
        T t;
        t.u.data.v *= rhs.u.data.v;
        return t;
    }
    inline T operator*(const T& rhs) { // matrix product
        T t;
        t.u.data.v *= rhs.u.data.v;
        return t;
    }
};


class Mat4i: public Mat4Base<mat4u<__m128i, int>, int, Mat4i> { // 4x4 int
public:
    inline Mat4i operator+=(const Mat4i& rhs);
    inline Mat4i operator-=(const Mat4i& rhs);
    inline Mat4i operator*=(const int rhs);
    inline Mat4i operator*=(const Mat4i& rhs);
};


class Mat4f: public Mat4Base<mat4u<__m128, float>, float, Mat4f> { // 4x4 float
public:
    inline Mat4i operator+=(const Mat4i& rhs);
    inline Mat4i operator-=(const Mat4i& rhs);
    inline Mat4i operator*=(const int rhs);
    inline Mat4i operator*=(const Mat4i& rhs);
};



} // xs_core
#endif // XS_CORE_MAT4_SSE__
