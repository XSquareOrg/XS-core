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

#ifndef XS_CORE_MM4__
#define XS_CORE_MM4__

#include "mm_basemaths.hpp"
#include "mm3and4com.hpp"

namespace xs_core {

// horizontal add funcs
float _hadd4f(__m128 v);
int _hadd4i(__m128i v);


struct float4u{
    union {
        __m128 v;
        float a[4]; // for access by index
    } data;
    float hadd(void) { // horizontal add
        float t = (this->data.a[0] + this->data.a[1]) +
            (this->data.a[2] + this->data.a[3]);
        return t;
    }
};


struct int4u{
    union {
        __m128i v;
        int a[4]; // for access by index
    } data;
    int hadd(void) { // horizontal add
        int t = (this->data.a[0] + this->data.a[1]) +
            (this->data.a[2] + this->data.a[3]);
        return t;
    }
};


template <class NUM, class T>
class _mm4: public mm_basemaths_T<NUM, T> { // common for 4 length mmXXXX classes
public:
    inline const unsigned size(void) {return 4;}
    inline T swizzled(int d[4]) {
        T t;
        t.swizzle(d);
        return *t;
    }
    inline T swizzled(int x, int y, int z, int w) {
        T t;
        t.swizzle(x, y, z, w);
        return *t;
    }
    inline void zero_axises(const bool v[4]) {
        if (!v[0]) this->u.data.a[0] = 0;
        if (!v[1]) this->u.data.a[1] = 0;
        if (!v[2]) this->u.data.a[2] = 0;
        if (!v[3]) this->u.data.a[3] = 0;
    }
    inline void zero_axises(T v) {
        if (v[0] <= 0) this->u.data.a[0] = 0;
        if (v[1] <= 0) this->u.data.a[1] = 0;
        if (v[2] <= 0) this->u.data.a[2] = 0;
        if (v[3] <= 0) this->u.data.a[3] = 0;
    }
    inline void zero_axises(const int v[4]) {
        if (!v[0]) this->u.data.a[0] = 0;
        if (!v[1]) this->u.data.a[1] = 0;
        if (!v[2]) this->u.data.a[2] = 0;
        if (!v[3]) this->u.data.a[1] = 0;
    }
};


template <class T>
class mm4f: public _mm4<float, T>,  public mm128<T>{ // float
protected:
    float4u u;
public:
    inline void set(const float x, const float y, const float z, const float w) {
        this->u.data.v = _mm_set_ps(w, z, y, x);
    }
    inline void set(float data[4]) {
        this->u.data.v = _mm_set_ps(data[3], data[2], data[1], data[0]);
    }
    inline void fill(const float n) {this->u.data.v = _mm_set_ps1(n);}
    inline bool is_flat(void) {
        __m128 m = _mm_set_ps1(this->u.data.v[0]);
        return _mm_cmpeq_ps(this->u.data.v, m);
    }
    inline void swizzle(int x, int y, int z, int w) {
        __m128 m = _mm_set_ps(this->u.data.v);
        this->u.data.v = _mm_shuffle_ps(m, m, _MM_SHUFFLE(z, y, x, w));
        }
    inline void swizzle(int d[4]) {
        __m128i m = _mm_set_ps(this->u.data.v);
        this->u.data.v = _mm_shuffle_ps(m, m, _MM_SHUFFLE(d[2], d[1], d[0], d[3]));
    }
    inline void reverse(void) {this->u.data.v = _mm_setr_ps(this->u.data.v);}
};


template <class T>
class mm4i: public _mm4<int, T>,  public mm128i<T> {
    //public mm_basemaths_T<int, T> { // int
protected:
    int4u u;
public:
    inline void set(const int x, const int y, const int z, const int w) {
        this->u.data.v = _mm_set_epi32(w, z, y, x);
    }
    inline void set(int data[4]) {
        this->u.data.v = _mm_set_epi32(data[3], data[2], data[1], data[0]);
    }
    inline void fill(const int n) {this->u.data.v = _mm_set1_epi32(n);}
    inline bool is_flat(void);
    inline void swizzle(int x, int y, int z, int w) {
        __m128i m = _mm_set_epi32(this->u.data.v);
        this->u.data.v = _mm_shuffle_epi32(m, _MM_SHUFFLE(z, y, x, w));
    }
    inline void swizzle(int d[4]) {
        __m128i m = _mm_set_epi32(this->u.data.v);
        this->u.data.v = _mm_shuffle_epi32(m, _MM_SHUFFLE(d[2], d[1], d[0], d[3]));
    }
    inline void reverse(void) {this->u.data.v = _mm_setr_epi32(this->u.data.v);}
};


} // xs_core
#endif // XS_CORE_MM4__
