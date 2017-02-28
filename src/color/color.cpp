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

#include "color.hpp"

namespace xs_core {

inline bool RGB8::operator==(const RGBA8 &rhs) {
    return (this->u.data.a[0] == rhs.u.data.a[0] &&
            this->u.data.a[1] == rhs.u.data.a[1] &&
            this->u.data.a[2] == rhs.u.data.a[2] &&
            this->u.data.a[3] == rhs.u.data.a[3]);
}
inline bool RGB8::operator==(const RGB8 &rhs) {
    return (this->u.data.a[0] == rhs.u.data.a[0] &&
            this->u.data.a[1] == rhs.u.data.a[1] &&
            this->u.data.a[2] == rhs.u.data.a[2]);
}


inline bool RGB16::operator==(const RGBA16 &rhs) {
    return (this->u.data.a[0] == rhs.u.data.a[0] &&
            this->u.data.a[1] == rhs.u.data.a[1] &&
            this->u.data.a[2] == rhs.u.data.a[2] &&
            this->u.data.a[3] == rhs.u.data.a[3]);
}
inline bool RGB16::operator==(const RGB16 &rhs) {
    return (this->u.data.a[0] == rhs.u.data.a[0] &&
            this->u.data.a[1] == rhs.u.data.a[1] &&
            this->u.data.a[2] == rhs.u.data.a[2]);
}

} // xs_core
