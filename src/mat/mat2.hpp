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


#ifndef XS_CORE_MAT2__
#define XS_CORE_MAT2__

#include "../simd/simd_include.hpp"

namespace xs_core {


template <class MM, typename NUM>
class mat2u {
public:
    union {
        MM v;
        NUM a[4]; // a, b, c, d
    } data;
    const unsigned width = 2;
    const unsigned height = 2;
};


template <class U, typename NUM, class T>
class Mat2Base {
public:
    const unsigned width(void) {return 2;}
    const unsigned height(void) {return 2;}
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


class Mat2i: public Mat2Base<mat2u<__m128i, int>, int, Mat2i> { // 2x2 int
public:
    inline Mat2i operator+=(const Mat2i& rhs);
    inline Mat2i operator-=(const Mat2i& rhs);
    inline Mat2i operator*=(const int rhs);
    inline Mat2i operator*=(const Mat2i& rhs);
};


class Mat2f: public Mat2Base<mat2u<__m128, float>, float, Mat2f> { // 2x2 float
public:
    inline Mat2f operator+=(const Mat2f& rhs);
    inline Mat2f operator-=(const Mat2f& rhs);
    inline Mat2f operator*=(const float rhs);
    inline Mat2f operator*=(const Mat2f& rhs);
};


} // xs_core
#endif // XS_CORE_MAT2__
