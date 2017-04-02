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

// struct for 2d simd vector and vector-like objects

#ifndef XS_CORE_VUNION2__
#define XS_CORE_VUNION2__

namespace xs_core {

template <class _MM, typename NUM>
struct _VUnion2{
    unsigned size(void) {return 2;}
    union {
        _MM v;
        NUM a[2];
        struct {NUM x, y;} b;
    } data;
    NUM x(void) {return this->data.b.x;}
    NUM y(void) {return this->data.b.y;}
    NUM& operator[](const unsigned i) {return this->data.a[i];}
};

} // xs_core
#endif // XS_CORE_VUNION2
