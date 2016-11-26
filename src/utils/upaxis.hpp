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

#ifndef XS_CORE_UPAXIS__
#define XS_CORE_UPAXIS__

namespace xs_core {

class UpAxis {
    bool _invert = false;
    char _axis = 1;
public:
    UpAxis() {}
    UpAxis(bool invert, const unsigned axis) {
        if (axis <= 2)
            this->_axis = axis;
            this->_invert = invert;
    }
    ~UpAxis() {}
    bool is_inverted(void) {return this->_invert;}
    UpAxis inverted(void) {
        UpAxis x = *this;
        x.invert();
        return x;
    }
    void set_axis(const unsigned axis) {
        if (axis >= 0 || axis <= 2) this->_axis = axis;
    }
    void invert(void) {this->_invert = (this-_invert) ? false : true;}
    bool operator==(UpAxis &rhs) {
        return (this->_invert == rhs._invert && this->_axis == rhs._axis);
    }
    bool operator!=(UpAxis &rhs) {return !this->operator==(rhs);}
    operator int(void) {return (this->_invert) ? -this->_axis : this->_axis;}
    operator unsigned(void) {return this->_axis;} // like abs/for index
    operator const char*(void) const{
        if (this->_invert) {
            if (this->_axis == 1) {
                const char* t = "-y";
                return t;
            } else {
                const char* t = (this->_axis == 2) ? "-z" : "-x";
                return t;
            }
        } else {
            if (this->_axis == 1) {
                const char *t = "y";
                return t;
            } else {
                const char* t = (this->_axis == 2) ? "z" : "x";
                return t;
            }
        }
    }
};

} // xs_core
#endif // XS_CORE_UPAXIS__
