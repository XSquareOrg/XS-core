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

#ifndef XS_CORE_UTILS_PACKFILL__
#define XS_CORE_UTILS_PACKFILL__

namespace XS_CORE {

// packing funcs
template <typename NUM>
const NUM* packed_2(const NUM x, const NUM y) {
    NUM* t;
    t[0] = x;
    t[1] = y;
    return t;
}
template <typename NUM>
const NUM* packed_3(const NUM x, const NUM y, const NUM z) {
    NUM* t;
    t[0] = x;
    t[1] = y;
    t[2] = z;
    return t;
}
template <typename NUM>
const NUM* packed_4(const NUM x, const NUM y, const NUM z, const NUM w) {
    NUM* t;
    t[0] = x;
    t[1] = y;
    t[2] = z;
    t[3] = w;
    return t;
}


// filling funcs
template <typename NUM>
const NUM* filled_2(const NUM v) {
    NUM* t;
    t[0] = v;
    t[1] = v;
    return t;
}
template <typename NUM>
const NUM* filled_3(const NUM v) {
    NUM* t;
    t[0] = v;
    t[1] = v;
    t[2] = v;
    return t;
}
template <typename NUM>
const NUM* filled_4(const NUM v) {
    NUM* t;
    t[0] = v;
    t[1] = v;
    t[2] = v;
    t[3] = v;
    return t;
}


} // XS_CORE
#endif // XS_CORE_UTILS_PACKFILL__
