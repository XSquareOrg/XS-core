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

#ifndef XS_CORE_MM2__
#define XS_CORE_MM2__

#include "mm_basemaths.hpp"
#include "simd_include.hpp"

namespace xs_core {


template <class U, class T>
class _mm2: public mm_basemaths_T<U, T> {
    struct {U x, y;} data;
public:
    inline const unsigned size(void) {return 2;}
    inline void zero_axises(const bool* v[2]) {
        if (!v[0]) this->data.x = 0;
        if (!v[1]) this->data.y = 0;
    }
    inline void zero_axises(T v) {
        if (v[0] <= 0) this->data.x = 0;
        if (v[1] <= 0) this->data.y = 0;
    }
    inline void zero_axises(const int v[2]) {
        if (!v[0]) this->data.x = 0;
        if (!v[1]) this->data.y = 0;
    }
    inline void zero(void) {
        this->data.x = 0;
        this->data.y = 0;
    }
    inline T swizzled(int x, int y) {
        T t;
        t.swizzle(x, y);
        return t;
    }
    inline T swizzled(int d[2]) {
        T t;
        t.swizzle(d);
        return t;
    }
    inline void XY(void) {
        T t;
        return t;
    }
    inline bool operator!=(const T &rhs) {return !this->operator==(rhs);}
};


template <class T>
class mm_2: public _mm2<float, T> { // 32bit float
public:
    operator __m64();
    operator const __m64();
    inline void fill(const float n);
    inline void swizzle(int d[2]);
    inline void swizzle(int x, int y);
    inline void reverse(void);
    inline T operator+=(const T &rhs);
    inline T operator-=(const T &rhs);
    inline T operator*=(const T &rhs);
    inline T operator/=(const T &rhs);
    inline T operator^=(const T &rhs);
    inline bool operator==(const T &rhs);
    //inline bool operator!=(const T &rhs);
    inline void XX(void);
    inline void YY(void);
    inline void YX(void);
};


template <class T>
class mmi_2: public _mm2<int, T> { // 32bit integer
public:
    operator __m64();
    operator const __m64();
    void fill(const float n) {
        __m64 m = _mm_set1_pi32(n);
        this->data = m;
    }
    void zero(void) {
        __m64 m = _mm_setzero_si64();
        this->data = m;
    }
    void swizzle(int d[2]) {
        this->data.x = (d[0] <= 0) ? this->data.x : this->data.y;
        this->data.y = (d[1] <= 0) ? this->data.x : this->data.y;
    }
    void swizzle(int x, int y) {
        this->data.x = (x <= 0) ? this->data.x : this->data.y;
        this->data.y = (y <= 0) ? this->data.x : this->data.y;
    }
    inline void reverse(void) {
        __m64 m = _mm_setr_pi32(this->data);
        this->data = m;
    }
    inline T operator+=(const T &rhs) {
        __m64 m = _mm_add_pi32(this->data, rhs.data);
        this->data = m;
        return *this;
    }
    inline T operator-=(const T &rhs) {
        __m64 m = _mm_sub_pi32(this->data, rhs.data);
        this->data = m;
        return *this;
    }
    inline T operator*=(const T &rhs) {
        this->data.x *= rhs.data.x;
        this->data.y *= rhs.data.y;
        return *this;
    }
    inline T operator/=(const T &rhs) {
        this->data.x /= rhs.data.x;
        this->data.y /= rhs.data.y;
        return *this;
    }
    inline T operator^=(const T &rhs) {
        __m64 m = _mm_xor_si64(this->data, rhs);
        this->data = m;
    }
    inline bool operator==(const T &rhs) {
        return this.data.x == rhs.data.x && this.data.y == rhs.data.y;
    }
    //inline bool operator!=(const T &rhs);
    inline void XX(void) {
        __m64 m = _mm_set_pi32(this->data.x);
        this->data = m;
    }
    inline void YY(void) {
        __m64 m = _mm_set_pi32(this->data.y);
        this->data = m;
    }
    inline void YX(void) {
        __m64 m = _mm_setr_pi32(this->data);
        this->data = m;
    }
};


}// xs_core
#endif // XS_CORE_MM2__
