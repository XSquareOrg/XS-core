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


#ifndef XS_CORE_VEC_CVT__
#define XS_CORE_VEC_CVT__

#include "vec2.hpp"
#include "vec4.hpp"
#include <utility>

namespace xs_core {


// pack 2 vec2i types into a vec4i
Vec4i Vec4i_from_2_Vec2i(const Vec2i a, const Vec2i b) {
    Vec4i t;
    t.set(a[0], a[1], b[0], b[1]);
    return t;
}


// unpack a vec4i into a 2 vec2i
std::pair<Vec2i, Vec2i> Vec4i_to_2_Vec2i(const Vec4i v) {
    Vec2i a, b;
    a.set(v[0], v[1]);
    b.set(v[2], v[3]);
    std::pair<Vec2i, Vec2i> t;
    t = std::make_pair(a, b);
    return t;
}


} // xs_core
#endif // XS_CORE_VEC_CVT
