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

#include "mm3and4com.hpp"

namespace XS_CORE {

class Vec4f;


template <class U, class T>
class _mm4 { // common for 4 length mmXXXX classes
public:
    inline const unsigned size(void) {return 4;}
    inline T axial_sum(void) {
        return (this->data.x + this->data.y) + (this->data.z + this->data.w);
    }
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
        if (!v[0]) this->x = 0;
        if (!v[1]) this->y = 0;
        if (!v[2]) this->z = 0;
        if (!v[3]) this->w = 0;
    }
    inline void zero_axises(T v) {
        if (v[0] <= 0) this->x = 0;
        if (v[1] <= 0) this->y = 0;
        if (v[2] <= 0) this->z = 0;
        if (v[3] <= 0) this->w = 0;
    }
    inline void zero_axises(const int v[4]) {
        if (!v[0]) this->x = 0;
        if (!v[1]) this->y = 0;
        if (!v[2]) this->z = 0;
        if (!v[3]) this->w = 0;
    }
};


template <class T>
class mm128_4: public _mm4<float, T>,  public mm128<T> {
protected:
public:
    inline void set(float x, float y, float z, float w) {
        this->data = _mm_set_ps(w, z, y, x);
    }
    inline void set(float data[4]) {
        this->data = _mm_set_ps(data[3], data[2], data[1], data[0]);
    }
    inline void fill(float n) {this->data = _mm_set_ps1(n);}
    inline bool is_flat(void) {
        __m128 m = _mm_set_ps1(this->data[0]);
        return _mm_cmpeq_ps(this->data, m);
    }
    inline void swizzle(int x, int y, int z, int w) {
        __m128 m = _mm_set_ps(this->data);
        this->data = _mm_shuffle_ps(m, m, _MM_SHUFFLE(z, y, x, w));
        }
    inline void swizzle(int d[4]) {
        __m128i m = _mm_set_ps(this->data);
        this->data = _mm_shuffle_ps(m, m, _MM_SHUFFLE(d[2], d[1], d[0], d[3]));
    }
    inline void reverse(void) {this->data = _mm_setr_ps(this->data);}
};


template <class T>
class mm128i_4: public _mm4<int, T>,  public mm128i<T> {
protected:
public:
    inline void set(int x, int y, int z, int w) {
        this->data = _mm_set_epi32(w, z, y, x);
    }
    inline void set(int data[4]) {
        this->data = _mm_set_epi32(data[3], data[2], data[1], data[0]);
    }
    inline void fill(int n) {this->data = _mm_set1_epi32(n);}
    inline void swizzle(int x, int y, int z, int w) {
        __m128i m = _mm_set_epi32(this->data);
        this->data = _mm_shuffle_epi32(m, _MM_SHUFFLE(z, y, x, w));
    }
    inline void swizzle(int d[4]) {
        __m128i m = _mm_set_epi32(this->data);
        this->data = _mm_shuffle_epi32(m, _MM_SHUFFLE(d[2], d[1], d[0], d[3]));
    }
    inline void reverse(void) {this->data = _mm_setr_epi32(this->data);}
};

} // XS_CORE
#endif // XS_CORE_MM4__
