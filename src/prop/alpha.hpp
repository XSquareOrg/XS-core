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


#ifndef XS_CORE_ALPHAPROP__
#define XS_CORE_ALPHAPROP__

#include "../utils/clamp.hpp"

namespace xs_core {

class AlphaProp {
    // Clamped float value between 0.0 and 1.0
protected:
    float alpha;
public:
    inline operator bool() {return (this->alpha<0.5f) ? false : true;}
    inline operator int() {return (this->alpha<0.5f) ? 0 : 1;}
    inline operator unsigned() {return (this->alpha<0.5f) ? 0 : 1;}
    inline operator double() {return this->alpha;}
    inline operator float() {return this->alpha;}
    inline float get(void) {return this->alpha;}
    inline void set(const float a) {this->alpha = clamped(a, 0.0f, 1.0f);}
    inline bool operator==(const AlphaProp &rhs) {return this->alpha == rhs.alpha;}
    inline bool operator!=(const AlphaProp &rhs) {return !this->operator==(rhs);}
    inline bool operator<(const AlphaProp &rhs) {return !this->operator>=(rhs);}
    inline bool operator>(const AlphaProp &rhs) {return !this->operator<=(rhs);}
    inline bool operator<=(const AlphaProp &rhs) {return this->alpha > rhs.alpha;}
    inline bool operator>=(const AlphaProp &rhs) {return this->alpha < rhs.alpha;}

    inline bool operator==(const float rhs) {return this->alpha == rhs;}
    inline bool operator!=(const float rhs) {return !this->operator==(rhs);}
    inline bool operator<(const float rhs) {return !this->operator>=(rhs);}
    inline bool operator>(const float rhs) {return !this->operator<=(rhs);}
    inline bool operator<=(const float rhs) {return this->alpha > rhs;}
    inline bool operator>=(const float rhs) {return this->alpha < rhs;}
};

} // XS_CORE
#endif // XS_CORE_ALPHAPROP__
