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

// base classes for m128_3* and m128_4*

#ifndef XS_CORE_MM3AND4COM__
#define XS_CORE_MM3AND4COM__

#include "mm_basemaths.hpp"
//#include "veclikebase_T.hpp"

#if defined (__MINGW64__)
    #include <intrin.h>
#else
    #include <xmmintrin.h> // sse
    #include <emmintrin.h> // sse2
#endif

namespace XS_CORE {

template <class T>
class mm128: mm_basemaths_T<float, T> {
protected:
    __m128 data;
public:
    // raw conversion ops
    inline operator const __m128i() {
        const __m128i m = _mm_cvtepi_32_ps(this->data);
        return m;
    }
    inline operator __m128i() {
        __m128i m = _mm_cvtepi32_ps(this->data);
        return m;
    }
    inline operator const __m128() const {return *this->data;}
    inline operator __m128() {return *this->data;}
    inline void zero(void) {this->data = _mm_setzero_ps();}
    inline bool is_zero(void) {
        __m128 m = _mm_setzero_ps();
        return _mm_cmpeq_ps(this->data, m);
    }
    inline T max(const T &other) {
        T t = _mm_max_ps(this->data, other.data);
        return t;
    }
    inline void to_max(const T &other) {
        this->data = _mm_max_ps(this->data, other.data);
    }
    inline T min(const T &other) {
        T t = _mm_min_ps(this->data, other.data);
        return t;
    }
    inline void to_min(const T &other) {
        this->data = _mm_min_ps(this->data, other.data);
    }
    inline bool operator==(T rhs) {return _mm_cmpeq_ps(this->data, rhs);}
    inline bool operator!=(T rhs) {return _mm_cmpneq_ps(this->data, rhs);}
    inline T operator+=(T rhs) {
        this->data = _mm_add_ps(this->data, rhs);
        return *this;
    }
    inline T operator-=(T rhs) {
        this->data = _mm_sub_ps(this->data, rhs);
        return *this;
    }
    inline T operator*=(T rhs) {
        this->data = _mm_mul_ps(this->data, rhs);
        return *this;
    }
    inline T operator/=(T rhs) {
        this->data = _mm_div_ps(this->data, rhs);
        return *this;
    }
    inline T operator^=(T rhs) {
        this->data = _mm_xor_ps(this->data, rhs);
        return *this;
    }
};


template <class T>
class mm128i: mm_basemaths_T<int, T> {
protected:
    __m128i data;
public:
    // raw _m128x conversion ops
    inline operator const __m128i() const {return *this->data;}
    inline operator __m128i() {return *this->data;}
    inline operator const __m128() const {
        const __m128 m = _mm_cvtps_epi32(this->data);
        return m;
    }
    inline operator __m128() {
        __m128 m = _mm_cvtps_epi32(this->data);
        return m;
    }
    inline void zero(void) {this->data = _mm_setzero_si128();}
    inline bool is_zero(void) {
        __m128 m = _mm_setzero_si128();
        return _mm_cmpeq_ps(this->data, m);
    }
    inline T operator+=(const T &rhs) {
        this->data = _mm_add_epi32(this->data, rhs);
        return *this;
    }
    inline T operator-=(const T &rhs) {
        this->data = _mm_sub_epi32(this->data, rhs);
        return *this;
    }
    inline T operator*=(const T &rhs) {
        this->data = _mm_mul_epi32(this->data, rhs);
        return *this;
    }
    inline T operator/=(const T &rhs) {
        this->data = _mm_div_epi32(this->data, rhs);
        return *this;
    }
    inline T operator^=(const T &rhs) {
        this->data = _mm_xor_si128(this->data, rhs);
        return *this;
    }
    inline T operator>>(int i) {return _mm_srai_epi32(this->data);}
    inline T operator<<(int i) {return _mm_srli_epi32(this->data);}
};


} // XS_CORE
#endif // XS_CORE_MM3AND4COM__
