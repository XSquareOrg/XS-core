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

#ifndef XS_CORE_VEC2__
#define XS_CORE_VEC2__

#include "../simd/mm2.hpp"

namespace xs_core {

class Vec2i;
class Vec2d;

template <class NUM, class T>
class _V2Base {
// Mixin to provide funcs common to Vec2f and Vec2i
public:

    inline bool in_radius(const T r_center, const NUM r) {
        T n = this - r_center^2;
        return n[0] + n[1] < r^2;
    }
    inline bool outside_radius(const T r_center, const NUM r) {
        T n = this - r_center^2;
        return n[0] + n[1] <= r^2;
    }
};


class Vec2d: public _V2Base<Vec2d, double>, public mm2d<Vec2d> {
public:
    operator Vec2i();
    operator const Vec2i();
    Vec2d abs(void);
    Vec2d operator-() { // negation
        this->u.data.a[0] = -this->u.data.a[0];
        this->u.data.a[1] = -this->u.data.a[1];
        return *this;
    }
    double distance(const Vec2d v) {
        double2u u;
        __m128d m = _mm_sub_pd(this->u.data.v, v.u.data.v);
        m = _mm_mul_pd(m, m);
        u.data.v = m;
        return sqrt(u.hadd()); // return sqrt(_hadd2d(m));
    }
};


class Vec2i: public _V2Base<Vec2i, int>, public mm2i<Vec2i> {
public:
    operator Vec2d();
    operator const Vec2d();
    Vec2i abs(void);
    Vec2i operator-() { // negation
        this->u.data.a[0] = -this->u.data.a[0];
        this->u.data.a[1] = -this->u.data.a[1];
        return *this;
    }
    int distance(const Vec2i v) {
        int2u u;
        u.data.v = _mm_sub_pi32(this->u.data.v, v.u.data.v);
        u.data.a[0] *= u.data.a[0];
        u.data.a[1] *= u.data.a[1];
        return sqrt(u.hadd()); // return sqrt(_hadd2i(m));
    }
};


} // xs_core
#endif // XS_CORE_VEC2__
