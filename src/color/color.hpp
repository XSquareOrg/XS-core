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
#include "../simd/vunion.hpp"
#include "../utils/clamp.hpp"
//#include "colspace.hpp"

namespace xs_core {

void _clamp_8bitcol(char n) { n = (n <= 0) ? 0 : n;}
void _clamp_16bitcol(short n); // TODO

// TODO char and short have good usable sse* hadd funcs (I think?)

// 8-bit
struct char3u: _VUnion3<__m64, char> { // RGB
};
struct char4u: _VUnion4<__m64, char> { // RGBA
    char havg_no_alpha(void) { //
        return ((this->data.b.x + this->data.b.y) + this->data.b.z) / 3;
    }
};

// 16-bit
struct short3u: _VUnion3<__m64, char> { // RGB
};

struct short4u: _VUnion4<__m64, char> { // RGBA
    short havg_no_alpha(void) { //
        return ((this->data.b.x + this->data.b.y) + this->data.b.z) / 3;
    }
};

// forward declarations
class RGB8;
class RGBA8;
class RGB16;
class RGBA16;

// FIXME fills need to take into account existing alpha values
//  (need to add fill funcs for each rgba class?)

/* ---- Bases --------------------------------------------------------------- */
template <class T>
class _rgb_a_com { // common to both rgb & rgba types
public:
    // red channel
    T R(void) {return this->u.data.b.x;}
    const T R(void) const {return this->u.data.b.x;}
    // green channel
    T G(void) {return this->u.data.b.y;}
    const T G(void) const {return this->u.data.b.y;}
    // blue channel
    T B(void) {return this->u.data.b.z;}
    const T B(void) const {return this->u.data.b.z;}
};


template <class T>
class RGB_Base: public _rgb_a_com<T> { // base class for rgb types only
public:
    const unsigned size(void) {return 3;}
    virtual inline T blended(const T& rhs, const float offset);
    T BGR(void) {
        T t = this;
        t.reverse;
        return t;
    }
    bool has_alpha(void) {return false;} // has alpha channel

    void desaturate_avg(void) { // desaturate based on average
        this->fill(this->u.havg());
    }
    void desaturate_lum(void) { // desaturate based on luminosity
        this->fill(max3(this->u.data.b.x,
                this->u.data.b.y, this->u.data.b.z));
    }
};


template <class T>
class RGBA_Base: public _rgb_a_com<T> { // base class for rgba types only
    const unsigned size(void) {return 4;}
    T A(void) {return this->u.data.b.w;}
    const T A(void) const {return this->u.data.b.w;}
    T BGRA(void) {
        T t = this;
        t.reverse;
        return t;
    }
    bool has_alpha(void) {return true;} // has alpha channel
    inline T blended(const T& rhs, const float offset);

    void desaturate_avg(void) { // desaturate based on average
        this->fill(this->u.havg_no_alpha());
    }
    void desaturate_lum(void) { // desaturate based on luminosity
        this->fill(max4(this->u.data.b.x, this->u.data.b.y,
                this->u.data.b.z, this->u.data.b.w));
    }
};


template <class T>
class _8bitColBase {
public:
    void fill(const char n) {
        if (n <= 0) this->u.data.v = _mm_set_pi8(0, 0, 0, 0, 0, 0, 0, 0);
        else this->u.data.v = _mm_set_pi8(n, n, n, 0, 0, 0, 0, 0);
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
        if (n <= 0) this->u.data.v = _mm_set_pi16(0, 0, 0, 0);
        // FIXME max?
        else this->u.data.v = _mm_set_pi16(n, n, n, 0);
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
class RGB8: public RGB_Base<char>, public _8bitColBase<RGB8> {
protected:  // 8bit rgb
    char3u u;
public:
    const char colorspace(void) const {return 2;}
    friend class RGBA8;
    operator RGBA8();
    operator RGBA16();
    operator RGB16();
    void set(short n[3]) {set(n[0], n[1], n[2]);}
    void set(short r, short g, short b) {
        _clamp_8bitcol(r);
        _clamp_8bitcol(g);
        _clamp_8bitcol(b);
        this->u.data.v = _mm_set_pi8(r, g, b, 0, 0, 0, 0, 0);
        _mm_empty();
    }
    void invert(void) {
        __m64 x = _mm_set_pi8(255, 255, 255, 0, 0, 0, 0, 0);
        this->u.data.v = _mm_sub_pi8(this->u.data.v, x);
        _mm_empty();
    }
    inline void blend(const RGB8& rhs, const float offset);
    void reverse(void) {
        #ifdef HAS_SSSE3__ // TODO
        // _mm_shuffle_pi8() // ssse3
        #else
        this->u.data.v = _mm_set_pi8(
            this->u.data.b.z, this->u.data.b.y, this->u.data.b.x, 0,
            0, 0, 0, 0);
        _mm_empty();
        #endif
    }


    inline bool operator==(const RGBA8& rhs); // defined in color.cpp
    inline bool operator!=(const RGBA8& rhs) {return !this->operator==(rhs);}
    inline bool operator==(const RGB8& rhs); // defined in color.cpp
    inline bool operator!=(const RGB8& rhs) {return !this->operator==(rhs);}
};


class RGBA8: public RGBA_Base<char>, public _8bitColBase<RGBA8> {
protected:  // 8bit rgba
    char4u u;
public:
    const char colorspace(void) const {return 3;}
    friend class RGB8;
    operator RGB8();
    operator RGB16();
    operator RGBA16();
    void set(short n[4]) {set(n[0], n[1], n[2], n[3]);}
    void set(short r, short g, short b, short a) {
        _clamp_8bitcol(r);
        _clamp_8bitcol(g);
        _clamp_8bitcol(b);
        _clamp_8bitcol(a);
        this->u.data.v = _mm_set_pi8(r, g, b, a, 0, 0, 0, 0);
        _mm_empty();
    }
    inline void invert(void) {
        __m64 x = _mm_set_pi8(255, 255, 255, 255, 0, 0, 0, 0);
        this->u.data.v = _mm_sub_pi8(this->u.data.v, x);
        _mm_empty();
    }
    inline void blend(const RGBA8 &rhs, const float offset);
    void reverse(void) {
        #ifdef XSKERN_HAS_SSSE3__ // TODO -- not implemented
        // this->u.data.v = _mm_shuffle_pi8();
        #else
        this->u.data.v = _mm_set_pi8(
            this->u.data.b.z, this->u.data.b.y,
            this->u.data.b.x, this->u.data.b.w,
            0, 0, 0, 0);
        _mm_empty();
        #endif
    }
    void make_fully_opaque(void) {this->u.data.b.w = 255;}
    void make_fully_transparent(void) {this->u.data.b.w = 0;}
    bool is_opaque(void) {return this->u.data.b.w == 255;}

    inline bool operator==(const RGBA8& rhs) {
        return (this->u.data.b.x == rhs.u.data.b.x &&
                this->u.data.b.y == rhs.u.data.b.y &&
                this->u.data.b.z == rhs.u.data.b.z &&
                this->u.data.b.w == rhs.u.data.b.w);
    }
    inline bool operator!=(const RGBA8& rhs) {return !this->operator==(rhs);}

    /* --- RGBA8 - RGB8 eq/ne comparison --- */
    inline bool operator==(const RGB8& rhs) {
        //__m64 x = _mm_set_pi8(this->u.data.b.x, u.data.b.y, u.data.b.z, 0,
        //    0, 0, 0, 0);
        // _cmp_eq_(this.u.data.v, x)

        // will use the above in the future but for now this is better
        return _vunion3_eq_vunion4(rhs.u, this->u);
    }
    inline bool operator!=(const RGB8& rhs) {
        //__m64 x = _mm_set_pi8(this->u.data.b.x, u.data.b.y, u.data.b.z, 0,
        //      0, 0, 0, 0);
        // _cmp_ne_(this.u.data.v, x)

        // will use the above in the future but for now this is better
        return _vunion3_ne_vunion4(rhs.u, this->u);
    }
};


/* ---- 16 bit (packed as a short int) -------------------------------------- */
class RGB16: public RGB_Base<short>, public _16bitColBase<RGB16> {
protected:  // 16bit rgb
    short3u u;
public:
    const char colorspace(void) const {return 4;}
    friend class RGBA16;
    operator RGB8();
    void set(short n[3]) {set(n[0], n[1], n[2]);}
    void set(short r, short b, short g) {
        /*_clamp_16bitcol(r);
        _clamp_16bitcol(g);
        _clamp_16bitcol(b);
        */
        this->u.data.v = _mm_set_pi16(r, b, g, 0);
        _mm_empty();
    }
    void invert(void);
    void reverse(void) {
        this->u.data.v = _mm_set_pi16(
            this->u.data.b.x, this->u.data.b.y, this->u.data.b.z, 0);
        _mm_empty();
    }
    inline void blend(const RGB16 &rhs, const float offset);

    inline bool operator==(const RGB16& rhs); // defined in color.cpp
    inline bool operator!=(const RGB16& rhs) {return !this->operator==(rhs);}

    /* --- RGB16 - RGBA16 eq/ne comparison --- */
    inline bool operator==(const RGBA16& rhs); // defined in color.cpp
    inline bool operator!=(const RGBA16& rhs) {return !this->operator==(rhs);}
};


class RGBA16: public RGBA_Base<short>, public _16bitColBase<RGBA16> {
protected:  // 16 bit rgba
    short4u u;
public:
    const char colorspace(void) const {return 5;}
    friend class RGB16;
    operator RGB8();
    operator RGBA8();
    operator RGB16();
    void set(short n[3]) {set(n[0], n[1], n[2], n[3]);}
    void set(short r, short b, short g, short a) {
        /*_clamp_16bitcol(r);
        _clamp_16bitcol(g);
        _clamp_16bitcol(b);
        _clamp_16bitcol(a);*/
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
            this->u.data.b.z, this->u.data.b.y,
            this->u.data.b.x, this->u.data.b.w);
        _mm_empty();
    }
    inline void blend(const RGBA16 &rhs, const float offset);
    //void make_fully_opaque(void) {this->u.data.b.w = 1.0;}
    //void make_fully_transparent(void) {this->u.data.b.w = 1.0;}
    //bool is_opaque(void) {return this->u.data.b.w == 1.0f;}

    inline bool operator==(const RGBA16& rhs) {
        return (this->u.data.b.x == rhs.u.data.b.x &&
                this->u.data.b.y == rhs.u.data.b.y &&
                this->u.data.b.z == rhs.u.data.b.z &&
                this->u.data.b.w == rhs.u.data.b.w);
    }
    inline bool operator!=(const RGBA16& rhs) {return !this->operator==(rhs);}

    /* --- RGBA16-RGB16 eq/ne comparison between --- */
    // Note that input order is reversed
    inline bool operator==(const RGB16& rhs) {
        // x = _mm_set_pi16(this.u.b.z, this.u.b.y, this.u.b.x, 0);
        // _mm_cmp_eq_(x, rhs.u.v);
        return _vunion3_eq_vunion4(rhs.u, this->u);
    }
    inline bool operator!=(const RGB16& rhs) {
        // x = _mm_set_pi16(this.u.b.z, this.u.b.y, this.u.b.x, 0);
        // _mm_cmp_ne_(x, rhs.u.v);
        return _vunion3_ne_vunion4(rhs.u, this->u);
    }
};

// aliases
// typedef RGB16 RGB;
// typedef RGBA16 RGBA:

} // xs_core
#endif // XS_CORE_COLOR__
