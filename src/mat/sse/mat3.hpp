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


#ifndef XS_CORE_MAT3_SSE__
#define XS_CORE_MAT3_SSE__


// SSE* version
#include "../../simd/simd_include.hpp"

namespace xs_core {


template <class MM, typename NUM>
class mat3u {
public:
    // data is stored as 3 4d arrays the last item is not used
    union {NUM a[4]; MM v;} x; // a b c X
    union {NUM a[4]; MM v;} y; // d e f X
    union {NUM a[4]; MM v;} z; // g h i X
    const unsigned width = 3;
    const unsigned height = 3;
};


template <class U>
class Mat3Base {
    U u;
public:
    const unsigned width(void) {return 3;}
    const unsigned height(void) {return 3;}
    bool is_square(void) {return true;}
};


class Mat3i: public Mat3Base<mat3u<__m128i, int>> { // 3x3 int
public:
};

class Mat3f: public Mat3Base<mat3u<__m128, float>> { // 3x3 float
public:
};


} // xs_core
#endif // XS_CORE_MAT3_SSE__
