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

// same as refcount.hpp except without fake user

#ifndef XS_CORE_REFCOUNT__
#define XS_CORE_REFCOUNT__

//#include <mutex>
//#include <memory>

namespace xs_core {

class RefCount_NoFake {
protected:
    unsigned _users;
public:
    RefCount() {}
    ~RefCount() {}
    bool has_fakeuser(void) {return false;}
    bool has_users(void) { return (!this->_fakeuser && this->_users == 0); }
    unsigned users(void) {this->_users;}
    operator const unsigned() const {return this->_users;}
    operator unsigned() {return this->_users;}
    void operator--(void) {
        if (this->_users >= 1) this->_users--;
    }
    void operator++(void) {this->_users++;}
    bool operator==(unsigned rhs) {return rhs == this->_users;}
    bool operator!=(unsigned rhs) { return (!this->operator==(rhs));}
    bool operator<=(unsigned rhs) {this->_users <= rhs;}
    bool operator>=(unsigned rhs) {this->_users >= rhs;}
    bool operator>(unsigned rhs) {this->_users > rhs;}
    bool operator<(unsigned rhs) {this->_users < rhs;}
};

} // xs_core
#endif // XS_CORE_REFCOUNT__
