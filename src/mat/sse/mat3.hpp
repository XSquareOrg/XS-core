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

#ifndef XS_CORE_MAT3_SSE__
#define XS_CORE_MAT3_SSE__


// SSE* version
#include "../../simd/simd_include.hpp"

namespace xs_core {


template <class MM, typename NUM>
class mat3u {
public:
    // data is stored as 3 4d arrays (the last item is not used)
    union {NUM a[4]; MM v;} x; // a b c X
    union {NUM a[4]; MM v;} y; // d e f X
    union {NUM a[4]; MM v;} z; // g h i X
    const unsigned width = 3;
    const unsigned height = 3;
};

typedef mat3u<__m128i, int> mat3ui;
typedef mat3u<__m128, float> mat3uf;

void _set_mat3i(mat3ui targ,
        const int a, const int b, const int c,
        const int d, const int e, const int f,
        const int g, const int h, const int i) {
    // Linear fill for 3x3 int
    targ.x.v = _mm_set_epi32(a, b, c, 0);
    targ.y.v = _mm_set_epi32(d, e, f, 0);
    targ.z.v = _mm_set_epi32(g, h, i, 0);
}
void _set_mat3f(mat3uf targ,
        const float a, const float b, const float c,
        const float d, const float e, const float f,
        const float g, const float h, const float i) {
    // Linear fill for 3x3 float
    targ.x.v = _mm_set_ps(a, b, c, 0);
    targ.y.v = _mm_set_ps(d, e, f, 0);
    targ.z.v = _mm_set_ps(g, h, i, 0);
}
__m128i _get_col_mat3i(const mat3ui targ, const unsigned i) {
    // get column from a mat3ui as an __m128i
    __m128i x = _mm_set_epi32(targ.x.a[i], targ.y.a[i], targ.z.a[i], 0);
    return x;
}
__m128 _get_col_mat3f(const mat3uf targ, const unsigned i) {
    // get column from a mat3uf as an __m128
    __m128 x = _mm_set_ps(targ.x.a[i], targ.y.a[i], targ.z.a[i], 0);
    return x;
}
void _set_col_mat3i(mat3uf targ, unsigned i, int x, int y, int z) {
    targ.x.a[i] = x;
    targ.y.a[i] = y;
    targ.z.a[i] = z;
}
void _set_col_mat3f(mat3uf targ, unsigned i, float x, float y, float z) {
    targ.x.a[i] = x;
    targ.y.a[i] = y;
    targ.z.a[i] = z;
}


template <class U, typename NUM, class T>
class Mat3Base {
protected:
    U u;
public:
    const unsigned width(void) {return 3;}
    const unsigned height(void) {return 3;}
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


class Mat3i: public Mat3Base<mat3ui, int, Mat3i> { // 3x3 int
public:
    inline void set(const int a, const int b, const int c,
            const int d, const int e, const int f,
            const int g, const int h, const int i) {
        _set_mat3i(this->u, a, b, c, d, e, f, g, h, i);
    }
    inline Mat3i operator+=(const Mat3i& rhs);
    inline Mat3i operator-=(const Mat3i& rhs);
    inline Mat3i operator*=(const int rhs);
    inline Mat3i operator*=(const Mat3i& rhs);
    inline bool operator==(const Mat3i& rhs);
    inline bool operator!=(const Mat3i& rhs);
};

class Mat3f: public Mat3Base<mat3uf, int, Mat3i> { // 3x3 float
public:
    inline void set(const float a, const float b, const float c,
            const float d, const float e, const float f,
            const float g, const float h, const float i) {
        _set_mat3f(this->u, a, b, c, d, e, f, g, h, i);
    }
    inline Mat3f operator+=(const Mat3f& rhs);
    inline Mat3f operator-=(const Mat3f& rhs);
    inline Mat3f operator*=(const float rhs);
    inline Mat3f operator*=(const Mat3f& rhs);
    inline bool operator==(const Mat3f& rhs);
    inline bool operator!=(const Mat3f& rhs);
};


} // xs_core
#endif // XS_CORE_MAT3_SSE__
