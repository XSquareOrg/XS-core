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


#ifndef XS_CORE_INPUTDEV__
#define XS_CORE_INPUTDEV__

#include "../inputbase.hpp"

namespace xs_core {


enum class mousebuttons {LEFT=0, RIGHT=1, MIDDLE=2, BUTTON1=3, BUTTON2=4};


class Mouse: public _Mouse {
protected:
    struct {bool l, r, m, b1, b2;} pressed;
public:
    void _update(void);
    bool has_pressed(void) {
        return (this->pressed.l || this->pressed.r || this->pressed.m ||
            this->pressed.b1 || this->pressed.b2);
    }
    bool button1_ispressed(void) {return this->pressed.b1;}
    bool button2_ispressed(void) {return this->pressed.b2;}
};


class Keyboard: public _Keyboard {
public:
    void _update(void);
};


} // xs_core
#endif // XS_CORE_INPUTDEV__
