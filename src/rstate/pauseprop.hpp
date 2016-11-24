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

#ifndef XS_CORE_PAUSEPROP__
#define XS_CORE_PAUSEPROP__

namespace XS_CORE {

class PauseProp {
protected:
    bool _paused = false;
public:
    inline const bool get(void) const {return this->_paused;}
    inline bool get(void) {return this->_paused;}
    inline void set(int state) {
        if (!this->_paused == !state) this->_paused = state;
    }
    inline void set(bool state) {
        if (this->_paused != state) this->_paused = state;
    }
    inline void pause(void) {
        if (!this->_paused) this->_paused = true;
    }
    inline void unpause(void) {
        if (this->_paused) this->_paused = false;
    }
    inline void toggle(void) {this->_paused = ~this->_paused;}
    inline bool toggled(void) {
        this->_paused = ~this->_paused;
        return this->_paused;
    }
    inline operator const bool() {return this->_paused;}
    inline operator bool() {return this->_paused;}
    inline operator const int() {return this->_paused;}
    inline operator int() {return this->_paused;}
    inline operator const unsigned() {return this->_paused;}
    inline operator unsigned() {return this->_paused;}
    inline operator const char() {return this->_paused;}
    inline operator char() {return this->_paused;}
    inline bool operator==(bool rhs) {return this->_paused == rhs;}
    inline bool operator!=(bool rhs) {return this->_paused != rhs;}
    inline bool operator==(PauseProp &rhs) {
        return this->_paused == rhs._paused;
    }
    inline bool operator!=(PauseProp &rhs) {
        return !this->operator==(rhs);
    }
    inline bool operator~(void) {
        this->_paused = ~this->_paused;
        return this->_paused;
    }
};

} // XS_CORE
#endif // XS_CORE_PAUSEPROP_
