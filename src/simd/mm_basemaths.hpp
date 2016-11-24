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

#ifndef XS_CORE_MM_BASEMATHS__
#define XS_CORE_MM_BASEMATHS__

namespace XS_CORE {

template <class NUM, class T>
class mm_basemaths_T {
public:
    T filled(NUM n) {
        T t;
        t.fill(n);
        return *t;
    }
    T reversed(void) {
        T t;
        t.reverse();
        return *t;
    }
    T inverted(void) {
        T t;
        t.invert();
        return *t;
    }
    inline T operator!=(const T &rhs) {return !this->operator==(rhs);}
    inline T operator+(const T &rhs) {
        T x = this->operator+=(rhs);
        return x;
    }
    inline T operator-(const T &rhs) {
        T x = this->operator-=(rhs);
        return x;
    }
    inline T operator*(const T &rhs) {
        T x = this->operator/=(rhs);
        return x;
    }
    inline T operator/(const T &rhs) {
        T x = this->operator/=(rhs);
        return x;
    }
    inline T operator^(const T &rhs) {
        T x = this->operator^=(rhs);
        return x;
    }
};


} // XS_CORE
#endif // XS_CORE_MM_BASEMATHS__
