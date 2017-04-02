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

// structs for 3d and 4d simd vector and vector-like objects

#ifndef XS_CORE_VUNION__
#define XS_CORE_VUNION__

namespace xs_core {

template <class _MM, typename NUM>
struct _VUnion3 {
    unsigned size(void) {return 3;}
    union {
        _MM v;
        NUM a[3];
        struct {NUM x, y, z;} b;
    } data;
    NUM x(void) {return this->data.b.x;}
    NUM y(void) {return this->data.b.y;}
    NUM z(void) {return this->data.b.z;}
    NUM& operator[](const unsigned i) {return this->data.a[i];}
};


template <class _MM, typename NUM>
struct _VUnion4 {
    unsigned size(void) {return 4;}
    union {
        _MM v;
        NUM a[4];
        struct {NUM x, y, z, w;} b;
    } data;
    NUM x(void) {return this->data.b.x;}
    NUM y(void) {return this->data.b.y;}
    NUM z(void) {return this->data.b.z;}
    NUM w(void) {return this->data.b.w;}
    NUM& operator[](const unsigned i) {return this->data.a[i];}

};

} // xs_core
#endif // XS_CORE_VUNION__
