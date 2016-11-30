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

#ifndef XS_CORE_MM3__
#define XS_CORE_MM3__

#include "mm3and4com.hpp"

namespace xs_core {

// horizontal add funcs
float _hadd3f(__m128 v);
int _hadd3i(__m128i v);


typedef struct {
    union {
        __m128 v;
        float a[3]; // for access by index
    } data;
    float hadd(void) { // horizontal add
        float t = (this->data.a[0] + this->data.a[1]) + this->data.a[2];
        return t;
        }
} float3u;


typedef struct {
    union {
        __m128i v;
        int a[3]; // for access by index
    } data;
    int hadd(void) { // horizontal add
        int t = (this->data.a[0] + this->data.a[1]) + this->data.a[2];
        return t;
        }
} int3u;


template <typename NUM, class T>
class _mm3 { // common for 3 length mmXXXX classes
public:
    inline const unsigned size(void) {return 3;}
    bool is_flat(bool) {
        return (this->u.data.a[0] == this->u.data.a[1]) == this->data.a[2];
    }
    inline T swizzled(int d[3]) {
        T t;
        t.swizzle(d);
        return t;
    }
    inline T swizzled(int x, int y, int z) {
        T t;
        t.swizzle(x, y, z);
        return t;
    }
    inline T filled(NUM n) {
        T t;
        t.fill(n);
        return t;
    }
    inline void zero_axises(const bool v[3]) {
        if (!v[0]) this->u.data.a[0] = 0;
        if (!v[1]) this->u.data.a[1] = 0;
        if (!v[2]) this->u.data.a[2] = 0;
    }
    inline void zero_axises(T v) {
        if (v[0] <= 0) this->u.data.a[0] = 0;
        if (v[1] <= 0) this->u.data.a[1] = 0;
        if (v[2] <= 0) this->u.data.a[2] = 0;
    }
    inline void zero_axises(const int v[3]) {
        if (!v[0]) this->u.data.a[0] = 0;
        if (!v[1]) this->u.data.a[1] = 0;
        if (!v[2]) this->u.data.a[2] = 0;
    }
};


template <class T>
class mm3f: _mm3<float, T>, mm128<T> { // float
protected:
    float3u u;
public:
    inline void set(float x, float y, float z) {
        this->u.data.v = _mm_set_ps(z, y, x, 0);
    }
    inline void set(float data[3]) {
        this->u.data.v = _mm_set_ps(data[2], data[1], data[0], 0);
    }
    inline void fill(float n) {this->u.data.v = _mm_set_ps(n, n, n, 0);}
    inline void swizzle(int x, int y, int z) {
        __m128 m = _mm_set_ps(this->u.data.v);
        this->u.data.v = _mm_shuffle_ps(m, m, _MM_SHUFFLE(z, y, x, 0));
    }
    inline void swizzle(int d[3]) {
        __m128i m = _mm_set_ps(this->u.data.v);
        this->u.data.v = _mm_shuffle_ps(m, m, _MM_SHUFFLE(d[2], d[1], d[0], 0));
    }
    inline void reverse(void) {
        __m128 m = _mm_set_ps(this->u.data.v);
        this->u.data.v = _mm_shuffle_ps(m, m, _MM_SHUFFLE(2,1,0,3));
    }
};


template <class T>
class mm3i: _mm3<int, T>, mm128i<T> { // int
protected:
    int3u u;
public:
    inline void set(int x, int y, int z) {
        this->u.data.v = _mm_set_epi32(z, y, x, 0);}
    inline void set(int data[3]) {
        this->u.data.v = _mm_set_epi32(data[2], data[1], data[0], 0);
    }
    inline void fill(int n) {this->u.data.v = _mm_set_epi32(n, n, n, 0);}
    inline void swizzle(int x, int y, int z) {
        __m128i m = _mm_set_epi32(this->u.data.v);
        this->u.data.v = _mm_shuffle_epi32(m, _MM_SHUFFLE(z, y, x, 3));
    }
    inline void swizzle(int d[3]) {
        __m128i m = _mm_set_epi32(this->u.data.v);
        this->u.data.v = _mm_shuffle_epi32(m, _MM_SHUFFLE(d[2], d[1], d[0], 0));
    }
    inline void reverse(void) {
        __m128i m = _mm_set_epi32(this->u.data.v);
        this->u.data.v = _mm_shuffle_epi32(m, _MM_SHUFFLE(2, 1, 0, 3));
    }
};


} // xs_core
#endif // XS_CORE_MM3__
