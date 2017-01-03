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


#ifndef XS_CORE_COLOR__
#define XS_CORE_COLOR__

#include "../simd/simd_include.hpp"

namespace xs_core {


struct char3u{
    union {
        __m64 v;
        char a[3];
    } data;
};


struct char4u{
    union {
        __m64 v;
        char a[4];
    } data;
};


struct short3u{
    union {
        __m64 v;
        short a[3];
    } data;
};


struct short4u{
    union {
        __m64 v;
        short a[4];
    } data;
};


// forward declarations
class RGB8;
class RGBA8;
class RGB16;
class RGBA16;


/* ---- Bases --------------------------------------------------------------- */
template <class T>
class _rgb_a_com { // common to both rgb & rgba types
public:
    // red channel
    T R(void) {return this->u.data.a[0];}
    const T R(void) const {return this->u.data.a[0];}
    // green channel
    T G(void) {return this->u.data.a[1];}
    const T G(void) const {return this->u.data.a[1];}
    // blue channel
    T B(void) {return this->u.data.a[2];}
    const T B(void) const {return this->u.data.a[2];}
};


template <class T>
class RGB_Base: public _rgb_a_com<T> { // base class for rgb types only
public:
    virtual inline T blended(const T& rhs, const float offset);
    T BGR(void) {
        T t = this;
        t.reverse;
        return t;
    }
};


template <class T>
class RGBA_Base: public _rgb_a_com<T> { // base class for rgba types only
    T A(void) {return this->u.data.a[3];}
    const T A(void) const {return this->u.data.a[3];}
    T BGRA(void) {
        T t = this;
        t.reverse;
        return t;
    }
    void make_fully_opaque(void) {this->u.data.a[3] = 1.0;}
    void make_fully_transparent(void) {this->u.data.a[3] = 1.0;}
    void is_opaque(void) {return this->u.data.a[3] == 1.0f;}
    inline T blended(const T& rhs, const float offset);
};


template <class T>
class _8bitColBase {
public:
    void fill(const char n) {
        this->u.data.v = _mm_set_pi8(n, n, n, 0, 0, 0, 0, 0);
        _mm_empty();
    }
    inline T operator+=(const T& rhs) {
        this->u.data.v = _mm_add_pi8(this->u.data.v, rhs.u.data.v);
        _mm_empty();
        return *this;
    }
    inline T operator-=(const T& rhs) {
        this->u.data.v = _mm_sub_pi8(this->u.data.v, rhs.u.data.v);
        _mm_empty();
        return *this;
    }
};


template <class T>
class _16bitColBase {
public:
    void fill(const short n) {
        // _mm_shuffle_pi16(this->u.data.v, imm8)
        this->u.data.v = _mm_set_pi16(n, n, n, 0);
        _mm_empty();
    }
    inline T operator+=(const T& rhs) {
        this->u.data.v = _mm_add_pi16(this->u.data.v, rhs.u.data.v);
        _mm_empty();
        return *this;
    }
    inline T operator-=(const T& rhs) {
        this->u.data.v = _mm_sub_pi16(this->u.data.v, rhs.u.data.v);
        _mm_empty();
        return *this;
    }
};

/* ---- 8 bit --------------------------------------------------------------- */
class RGB8: RGB_Base<char>, public _8bitColBase<RGB8> { // 8bit rgb
protected:
    char3u u;
public:
    operator RGBA8();
    operator RGBA16();
    operator RGB16();
    void invert(void);
    inline void blend(const RGB8& rhs, const float offset);
    void reverse(void) {
        // _mm_shuffle_pi8() // ssse3
        this->u.data.v = _mm_set_pi8(
            this->u.data.a[2], this->u.data.a[1], this->u.data.a[0], 0,
            0, 0, 0, 0);
        _mm_empty();
    }

    inline bool operator==(const RGBA8& rhs);
    inline bool operator!=(const RGBA8& rhs);
    inline bool operator==(const RGB8& rhs);
    inline bool operator!=(const RGB8& rhs);
};


class RGBA8: RGBA_Base<char>, public _8bitColBase<RGBA8> { // 8bit rgba
protected:
    char4u u;
public:
    operator RGB8();
    operator RGB16();
    operator RGBA16();
    void invert(void);
    inline void blend(const RGBA8 &rhs, const float offset);
    void reverse(void) {
        this->u.data.v = _mm_set_pi8(
            this->u.data.a[2], this->u.data.a[1],
            this->u.data.a[0], this->u.data.a[2],
            0, 0, 0, 0);
        _mm_empty();
    }
    inline bool operator==(const RGBA8& rhs);
    inline bool operator!=(const RGBA8& rhs);
    inline bool operator==(const RGB8& rhs);
    inline bool operator!=(const RGB8& rhs);
};


/* ---- 16 bit (packed as a short int) -------------------------------------- */
class RGB16: RGB_Base<short>, public _16bitColBase<RGB16> { // 16bit rgb
protected:
    short3u u;
public:
    operator RGB8();
    void set(short n[3]) {
        this->u.data.v = _mm_set_pi16(n[0], n[1], n[2], 0);
        _mm_empty();
    }
    void set(short r, short b, short g) {
        this->u.data.v = _mm_set_pi16(r, b, g, 0);
        _mm_empty();
    }
    void invert(void);
    void reverse(void) {
        this->u.data.v = _mm_set_pi16(
            this->u.data.a[0], this->u.data.a[1], this->u.data.a[2], 0);
        _mm_empty();
    }
    inline void blend(const RGB16 &rhs, const float offset);

    inline bool operator==(const RGB16& rhs);
    inline bool operator!=(const RGB16& rhs);
    inline bool operator==(const RGBA16& rhs);
    inline bool operator!=(const RGBA16& rhs);
};


class RGBA16: RGBA_Base<short>, public _16bitColBase<RGBA16> { // 16 bit rgba
protected:
    short4u u;
public:
    operator RGB8();
    operator RGBA8();
    operator RGB16();
    void set(short n[4]) {
        this->u.data.v = _mm_set_pi16(n[0], n[1], n[2], n[3]);
        _mm_empty();
    }
    void set(short r, short b, short g, short a) {
        this->u.data.v = _mm_set_pi16(r, b, g, a);
        _mm_empty();
    }
    void set_from_floats(float r, float b, float g, float a) {
        // sse
        __m128 m = _mm_set_ps(r, b, g, a);
        this->u.data.v = _mm_cvtps_pi16(m);
    }
    void invert(void);
    void reverse(void) {
        this->u.data.v = _mm_set_pi16(
            this->u.data.a[2], this->u.data.a[1],
            this->u.data.a[0], this->u.data.a[3]);
        _mm_empty();
    }
    inline void blend(const RGBA16 &rhs, const float offset);


    inline bool operator==(const RGBA16& rhs);
    inline bool operator!=(const RGBA16& rhs);
    inline bool operator==(const RGB16& rhs);
    inline bool operator!=(const RGB16& rhs);
};

// aliases
// typedef RGB16 RGB;
// typedef RGBA16 RGBA:

} // xs_core
#endif // XS_CORE_COLOR__
