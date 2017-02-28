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

typedef mat4u<__m128i, int> mat4ui;
typedef mat4u<__m128, float> mat4uf;

void _set_mat4i(mat4ui targ,
        const int a, const int b, const int c, const int d,
        const int e, const int f, const int g, const int h,
        const int i, const int j, const int k, const int l,
        const int m, const int n, const int o, const int p) {
    targ.x.v = _mm_set_epi32(a, b, c, d);
    targ.y.v = _mm_set_epi32(e, f, g, h);
    targ.z.v = _mm_set_epi32(i, j, k, l);
    targ.w.v = _mm_set_epi32(m, n, o, p);
}
void _set_mat4f(mat4uf targ,
        const float a, const float b, const float c, const float d,
        const float e, const float f, const float g, const float h,
        const float i, const float j, const float k, const float l,
        const float m, const float n, const float o, const float p) {
    targ.x.v = _mm_set_ps(a, b, c, d);
    targ.y.v = _mm_set_ps(e, f, g, h);
    targ.z.v = _mm_set_ps(i, j, k, l);
    targ.w.v = _mm_set_ps(m, n, o, p);
}
__m128i _get_col_mat3i(const mat4ui targ, const unsigned i) {
    // get column from a mat3ui as an __m128i
    __m128i x = _mm_set_epi32(targ.x.a[i], targ.y.a[i], targ.z.a[i], targ.w.a[i]);
    return x;
}
__m128 _get_col_mat3f(const mat4uf targ, const unsigned i) {
    // get column from a mat3uf as an __m128
    __m128 x = _mm_set_ps(targ.x.a[i], targ.y.a[i], targ.z.a[i], targ.w.a[i]);
    return x;
}
void _set_col_mat4i(mat4uf targ, unsigned i, int x, int y, int z, int w) {
    targ.x.a[i] = x;
    targ.y.a[i] = y;
    targ.z.a[i] = z;
    targ.w.a[i] = w;
}
void _set_col_mat4f(mat4uf targ, unsigned i, float x, float y, float z, float w) {
    targ.x.a[i] = x;
    targ.y.a[i] = y;
    targ.z.a[i] = z;
    targ.w.a[i] = w;
}


template <class U, typename NUM, class T>
class Mat4Base {
protected:
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


class Mat4i: public Mat4Base<mat4ui, int, Mat4i> { // 4x4 int
public:
    inline void set(const int a, const int b, const int c, const int d,
            const int e, const int f, const int g, const int h,
            const int i, const int j, const int k, const int l,
            const int m, const int n, const int o, const int p) {
        _set_mat4i(this->u, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);
    }
    inline Mat4i operator+=(const Mat4i& rhs);
    inline Mat4i operator-=(const Mat4i& rhs);
    inline Mat4i operator*=(const int rhs);
    inline Mat4i operator*=(const Mat4i& rhs);
    inline bool operator==(const Mat4i& rhs);
    inline bool operator!=(const Mat4i& rhs);
};


class Mat4f: public Mat4Base<mat4uf, float, Mat4f> { // 4x4 float
public:
    inline void set(const float a, const float b, const float c, const float d,
            const float e, const float f, const float g, const float h,
            const float i, const float j, const float k, const float l,
            const float m, const float n, const float o, const float p) {
        _set_mat4f(this->u, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);
    }
    inline Mat4i operator+=(const Mat4i& rhs);
    inline Mat4i operator-=(const Mat4i& rhs);
    inline Mat4i operator*=(const int rhs);
    inline Mat4i operator*=(const Mat4i& rhs);
    inline bool operator==(const Mat4f& rhs);
    inline bool operator!=(const Mat4f& rhs);
};


} // xs_core
#endif // XS_CORE_MAT4_SSE__
