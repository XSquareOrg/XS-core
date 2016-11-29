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


typedef struct {
    union {
        __m128 v;
        double a[2]; // for access by index
    } data;
    double hadd(void) { // horizontal add
        double t = (this->data.a[0] + this->data.a[1]);
        return t;
        }
} float2u;


typedef struct {
    union {
        __m64 v;
        int a[2]; // for access by index
    } data;
    int hadd(void) { // horizontal add
        int t = (this->data.a[0] + this->data.a[1]);
        return t;
        }
} int2u;


template <class NUM, class T>
class _mm2: public mm_basemaths_T<NUM, T> {
public:
    inline const unsigned size(void) {return this.u.size();}
    bool is_flat(void) {return this->u.data.a[0] == this->u.data.a[1];}
    inline void zero_axises(const bool* v[2]) {
        if (!v[0]) this->u.data.a[0] = 0;
        if (!v[1]) this->u.data.a[1] = 0;
    }
    inline void zero_axises(T v) {
        if (v[0] <= 0) this->u.data.a[0] = 0;
        if (v[1] <= 0) this->u.data.a[1] = 0;
    }
    inline void zero_axises(const int v[2]) {
        if (!v[0]) this->u.data.a[0] = 0;
        if (!v[1]) this->u.data.a[1] = 0;
    }
    inline void zero(void) {
        this->u.data.a[0] = 0;
        this->u.data.a[1] = 0;
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
class mm_2: public _mm2<double, T> { // double
    // no see funcs for 2 floats so use __m128 with 2 doubles instead
protected:
    float2u u;
public:
    operator __m64();
    operator const __m64();
    inline void fill(const double n);
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
protected:
    int2u u;
public:
    operator __m64() {return this->u.data.v;}
    operator const __m64() const {return this->u.data.v;}
    void fill(const int n) {
        this->u.data.v = _mm_set1_pi32(n);
        _mm_empty();
    }
    void zero(void) {
        this->u.data.v = _mm_setzero_si64();
        _mm_empty();
    }
    void swizzle(int d[2]) {
        this->u.data.a[0] = (d[0] <= 0) ? this->u.data.a[0] : this->u.data.a[1];
        this->u.data.a[1] = (d[1] <= 0) ? this->u.data.a[0] : this->u.data.a[1];
    }
    void swizzle(int x, int y) {
        this->u.data.a[0] = (x <= 0) ? this->u.data.a[0] : this->u.data.a[1];
        this->u.data.a[1] = (y <= 0) ? this->u.data.a[0] : this->u.data.a[1];
    }
    inline void reverse(void) {this->u.data.v = _mm_setr_pi32(this->u.data.v);}
    inline T operator+=(const T &rhs) {
        this->u.data.v = _mm_add_pi32(this->u.data.v, rhs.u.data.v);
        _mm_empty();
        return *this;
    }
    inline T operator-=(const T &rhs) {
        this->u.data.v = _mm_sub_pi32(this->u.data.v, rhs.u.data.v);
        _mm_empty();
        return *this;
    }
    inline T operator*=(const T &rhs) {
        this->u.data.a[0] *= rhs.u.data.a[0];
        this->u.data.a[1] *= rhs.u.data.a[1];
        return *this;
    }
    inline T operator/=(const T &rhs) {
        this->u.data.a[0] /= rhs.u.data.a[0];
        this->u.data.a[1] /= rhs.u.data.a[1];
        return *this;
    }
    inline T operator^=(const T &rhs) {
        __m64 m = _mm_xor_si64(this->u.data.v, rhs.u.data.v);
        this->u.data.v = m;
        _mm_empty();
    }
    inline bool operator==(const T &rhs) {
        return this.data.a[0] == rhs.u.data.a[0] &&
            this.u.data.a[1] == rhs.u.data.a[1];
    }
    //inline bool operator!=(const T &rhs);
    inline void XX(void) {
        __m64 m = _mm_set_pi32(this->u.data.a[0]);
        this->u.data.v = m;
        _mm_empty();
    }
    inline void YY(void) {
        __m64 m = _mm_set_pi32(this->u.data.a[1]);
        this->u.data.v = m;
        _mm_empty();
    }
    inline void YX(void) {
        __m64 m = _mm_setr_pi32(this->u.data.v);
        this->u.data.v = m;
        _mm_empty();
    }
};


}// xs_core
#endif // XS_CORE_MM2__
