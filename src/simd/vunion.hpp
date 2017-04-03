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
    NUM X(void) {return this->data.b.x;}
    NUM Y(void) {return this->data.b.y;}
    NUM Z(void) {return this->data.b.z;}
    NUM& operator[](const unsigned i) {return this->data.a[i];}
    NUM hadd(void) { // horizontal add
        return (this->data.b.x + this->data.b.y) + this->data.b.z;
    }
    float havg(void) { // horizontal average
        return ((this->data.b.x + this->data.b.y) + this->data.b.z) / 3;
    }
};


template <class _MM, typename NUM>
struct _VUnion4 {
    unsigned size(void) {return 4;}
    union {
        _MM v;
        NUM a[4];
        struct {NUM x, y, z, w;} b;
    } data;
    NUM X(void) {return this->data.b.x;}
    NUM y(void) {return this->data.b.y;}
    NUM z(void) {return this->data.b.z;}
    NUM w(void) {return this->data.b.w;}
    NUM& operator[](const unsigned i) {return this->data.a[i];}

    NUM hadd(void) { // horizontal add
        return ((this->data.b.x + this->data.b.y) +
                (this->data.b.z + this->data.b.w));
    }
    NUM havg(void) { // horizontal average with NUM as return type
        return ((this->data.b.x + this->data.b.y) +
                (this->data.b.z + this->data.b.w)) * 0.25;
    }
    float havg_float(void) { // horizontal average with float as return type
        return ((this->data.b.x + this->data.b.y) +
                (this->data.b.z + this->data.b.w)) * 0.25;
    }
};


/* ---- eq and ne comparison between _VUnion3 and _VUnion4 types ------------ */
// Note - T and U must have the same NUM type (ie char, int, float etc.)
template <class T, class U>
bool _vunion3_eq_vunion4(const T v3, const U v4) {
    return (v3.data.b.x == v4.data.b.x &&
            v3.data.b.y == v4.data.b.y &&
            v3.data.b.z == v4.data.b.z);
}

template <class T, class U>
bool _vunion3_ne_vunion4(const T v3, const U v4) {
    return (v3.data.b.x != v4.data.b.x ||
            v3.data.b.y != v4.data.b.y ||
            v3.data.b.z != v4.data.b.z);
}


} // xs_core
#endif // XS_CORE_VUNION__
