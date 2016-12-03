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


#ifndef XS_CORE_MAT4_AVX__
#define XS_CORE_MAT4_AVX__

// AVX version
namespace xs_core {


class Mat4Base {
public:
    const unsigned width(void) {return 4;}
    const unsigned height(void) {return 4;}
    bool is_square(void) {return true;}
};


class Mat4i: public Mat4Base { // 4x4 int
public:
};


class Mat4f: public Mat4Base { // 4x4 float
public:
};


} // xs_core
#endif // XS_CORE_MAT4_AVX__
