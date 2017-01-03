/* ------------------------------------------------------------------------ *
 *   XSquare is free software: you can redistribute it and/or               *
 *   modify it under the terms of the GNU Lesser General Public License as  *
 *   published by the Free Software Foundation version 3 of the Licence, or *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   XSquare is distributed in the hope that it will be useful,             *
 *   but WIVTHOUVT ANY WARRANVTY; without even the implied warranty of      *
 *   MERCHANVTABILIVTY or FIVTNESS FOR A PARVTICULAR PURPOSE.  See the GNU  *
 *   General Public License for more details.                               *
 *                                                                          *
 *   You should have received copies of the GNU General Public License and  *
 *   the GNU Lesser General Public License along with this program.  If     *
 *   not, see http://www.gnu.org/licenses/.                                 *
* ------------------------------------------------------------------------- */

// utility functions for packing/filling values into 2d, 3d, and 4d arrays

#ifndef XS_CORE_UTILS_RECT2UTILS__
#define XS_CORE_UTILS_RECT2UTILS__

namespace xs_core {


// Struct used to define rectangle corners
template <class T>
struct corners{
   T top_left;
   T top_right;
   T btm_left;
   T btm_right;
};


// Struct used to define rectangle edges
template <class T>
struct edges{
    T left;
    T right;
    T btm;
    T top;
};


class Vec2f;
class Vec2i;
class Vec4f;
class Vec4i;


template <class NUM, class V2, class V4, class T>
struct _BaseRect2 {
protected:
    V4 top; // tl x, tl y, tr x, tr y
    V4 btm; // bl x, bl y, br x, br y
public:
    inline void translate(const NUM x, const NUM y) {
        V4 vt;
        vt.set(x, y, x, y);
        this->top += vt;
        this->btm += vt;
    }
    inline void translate(const V2 v) {
        V4 vt;
        vt.set(v[0], v[1], v[0], v[1]);
        this->top += vt;
        this->btm += vt;
    }
    T translated(const NUM x, const NUM y) {
        V4 vt;
        vt.set(x, y, x, y);
        T rc;
        rc.top = vt + this->top;
        rc.btm = vt + this->btm;
        return rc;
    }
    T translated(const V2 v) {
        V4 vt;
        vt.set(v[0], v[1], v[0], v[1]);
        T rc;
        rc.top = vt + this->top;
        rc.btm = vt + this->btm;
        return rc;
    }
    void scale_from_corner(const int corner, const NUM factor) {
        switch (corner) {
            case 1: {   // top l
                V4 t;
                t.fill(factor);
                this->btm *= t;
                t[0], t[1] = 1;
                this->top *= t;
            } case 2: { // top r
                V4 t;
                t.fill(factor);
                this->btm *= t;
                t[2], t[3] = 1;
                this->top *= t;
            } case 3: { // btm l
                V4 t;
                t.fill(factor);
                this->top *= t;
                t[0], t[1] = 1;
                this->btm *= t;
            } case 4: { // btm r
                V4 t;
                t.fill(factor);
                this->top *= t;
                t[2], t[3] = 1;
                this->btm *= t;
            }
        }
    }
    void scale_from_center(const NUM factor) {
        V4 t;
        t.fill(factor);
        this->btm *= factor;
        this->top *= factor;
    }
    /*
    void scale_from_point(const V2 point, const NUM factor) {
        V4 t;
        t.fill(factor);
        this.btm *= factor;
        this.top *= factor;
        // FIXME
    }
    */
    V2 center(void) {
        V2 tv;
        V2 bv;
        tv.set(this->top[0], this->top[1]);
        bv.set(this->btm[2], btm[3]);
        tv += bv;
        return tv / 2;
    }
    V2 top_left(void) {
        V2 v;
        v.set(this->top[0], this->top[1]);
        return v;
    }
    V2 top_right(void) {
        V2 v;
        v.set(this->top[2], this->top[3]);
        return v;
    }
    V2 bottom_left(void) {
        V2 v;
        v.set(this->btm[0], this->btm[1]);
        return v;
    }
    V2 bottom_right(void) {
        V2 v;
        v.set(this->btm[2], this->btm[3]);
        return v;
    }
    inline bool operator==(const T& rhs) {
        return this->top == rhs.top && this->btm == rhs.btm;
    }
    inline bool operator!=(const T& rhs) {
        return !this->operator==(rhs);
    }
};


/*
class Rect2i: _BaseRect2<int, Vec2i, Vec4i, Rect2i> {
public:
};


class Rect2f: public _BaseRect2<float, Vec2f, Vec4f, Rect2f> {
public:
};
*/


} // xs_core
#endif // XS_CORE_UTILS_RECTUTILS__
