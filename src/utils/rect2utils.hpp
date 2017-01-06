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

#include "../vec/vec2.hpp"
#include "../vec/vec4.hpp"

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


class Vec2d;
class Vec2i;
class Vec4f;
class Vec4i;


/* Non-rotatable rectangle base class. */
template <class NUM, class V2, class T>
struct _BaseRect2 {
protected:
    V2 pos;  // position of top left corner
    V2 size; // width, height
    enum {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT} anchor;
public:
    bool is_square(void) {return this->size[0] == this->size[1];}
    const bool is_rotatable(void) const {return false;}
    /* ---- Size, Width, Height properties ---- */
    V2 get_size(void) {return this->_size;}
    void set_size(NUM x, NUM y) {
        this->size[0] = (x >= 0) ? x : 0;
        this->size[1] = (y >= 0) ? y : 0;
    }
    void set_size(V2 size) {this->set_size(size[0], size[1]);}
    NUM get_width(void) {return this->_size[0];}
    void set_width(NUM w) {this->size[0] = (w >= 0) ? w : 0;}
    NUM get_height(void) {return this->_size[1];}
    void set_height(NUM h) {this->size[1] = (h >= 0) ? h : 0;}
    /* ---- Translation Funcs ---- */
    void translate(const NUM x, const NUM y) {
        this->pos[0] += x;
        this->pos[1] += y;
    }
    inline void translate(const V2& pos) {this->pos += pos;}
    T translated(const NUM x, const NUM y) {
        T rect = *this->rect;
        rect.pos.set(x, y);
        rect.pos += this->pos;
        return rect;
    }
    T translated(const V2& pos) {
        T rect = *this->rect;
        return rect.pos += pos;
    }
    /* ---- Collision Detection ---- */
    bool is_inside(const V2 pt) {
        if (pt[0] < this->pos[0]) return false;
        else if (pt[0] > this->size[0]) return false;
        else if (pt[1] < this->pos[1]) return false;
        else if (pt[1] > this->size[1]) return false;
        else return true;
    }
    bool is_outside(const V2 pt) {
        if (pt[0] >= this->pos[0]) return false;
        else if (pt[0] <= this->size[0]) return false;
        else if (pt[1] >= this->pos[1]) return false;
        else if (pt[1] <= this->size[1]) return false;
        else return true;
    }
    //bool Rect2_has_intersection(const T& rhs); // TODO

    /* ---- Vector Positions ------------------------------- */
    V2 center(const bool local) {
        if (local) return this->size / 2;
        else return (this->size / 2) + this->pos;
    }
    /* ---- Corner Vector Positions ---- */
    V2 top_left(const bool local) {
        if (local) return this->pos;
        else {
            V2 v;
            v.set(0, 0);
            return v;
        }
    }
    V2 top_right(const bool local) {
        V2 v;
        v.set(this->size[0], this->pos[1]);
        if (!local) v += this->pos;
        return v;
    }
    V2 btm_left(const bool local) {
        V2 v;
        v.set(this->pos[0], this->size[1]);
        if (!local) v += pos;
        return v;
    }
    V2 btm_right(const bool local) {
        if (local) return this->size;
        else {
            V2 v = *this->size;
            v += this->pos;
            return v;
        }
    }
    inline bool operator==(const T& rhs) {
        return this->top == rhs.top && this->btm == rhs.btm;
    }
    inline bool operator!=(const T& rhs) {return !this->operator==(rhs);}
};


class Rect2i: public _BaseRect2<int, Vec2i, Rect2i> {
public:
};


class Rect2d: public _BaseRect2<double, Vec2d, Rect2d> {
public:
};



} // xs_core
#endif // XS_CORE_UTILS_RECTUTILS__
