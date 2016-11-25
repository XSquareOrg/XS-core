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

namespace XS_CORE {


template <class U, class T>
class _mm2: public mm_basemaths_T<U, T> {
public:
    inline const unsigned size(void) {return 2;}
    inline void zero_axises(const bool* v[2]) {
        if (!v[0]) this->x = 0;
        if (!v[1]) this->y = 0;
    }
    inline void zero_axises(T v) {
        if (v[0] <= 0) this->x = 0;
        if (v[1] <= 0) this->y = 0;
    }
    inline void zero_axises(const int v[2]) {
        if (!v[0]) this->x = 0;
        if (!v[1]) this->y = 0;
    }
    inline void zero(void) {
        this->x = 0;
        this->y = 0;
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
};


template <class T>
class mm_2: public _mm2<float, T> {
public:
    void fill(const float n);
    inline void swizzle(int d[2]);
    inline void swizzle(int x, int y);
    inline void reverse(void);
};


template <class T>
class mmi_2: public _mm2<int, T> {
public:
    void fill(const float n);
    inline void swizzle(int d[2]);
    inline void swizzle(int x, int y);
    inline void reverse(void);
};


}// XS_CORE
#endif // XS_CORE_MM2__
