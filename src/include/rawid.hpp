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


#ifndef XS_CORE_RAWID__
#define XS_CORE_RAWID__

namespace XS_CORE {

class RawID {
protected:
    unsigned rid = 0;
public:
    explicit RawID() {}
    explicit RawID(unsigned v) {this->rid = v;}
    virtual ~RawID();
    const unsigned &ID(void) {return this->rid;}
    operator const unsigned() {return this->rid;}
    operator unsigned() {return this->rid;}
    bool operator==(const RawID &rhs) {return this->rid == rhs.rid;}
    bool operator==(const unsigned &rhs) {return this->rid == rhs;}

    bool operator!=(const RawID &rhs) {return !this->operator==(rhs);}
    bool operator!=(const unsigned &rhs) {return !this->operator==(rhs);}

    bool operator<(const RawID &rhs) {return this->rid < rhs.rid;}
    bool operator<(const unsigned &rhs) {return this->rid < rhs;}

    bool operator>(const RawID &rhs) {return this->rid > rhs.rid;}
    bool operator>(const unsigned &rhs) {return this->rid > rhs;}

    bool operator<=(const RawID &rhs) {return this->rid <= rhs.rid;}
    bool operator<=(const unsigned &rhs) {return this->rid <= rhs;}

    bool operator>=(const RawID &rhs) {return this->rid >= rhs.rid;}
    bool operator>=(const unsigned &rhs) {return this->rid >= rhs;}
};


class MgrRawID: public RawID {
protected:
    unsigned _last = 0;
    bool _locked = false;
public:
    friend class RawID;
    MgrRawID() {
        this->rid++;
    }
    ~MgrRawID() {}
    bool operator==(const MgrRawID &rhs) {return this->rid == rhs.rid;}
    bool operator!=(const MgrRawID &rhs) {return !this->operator==(rhs);}
    RawID new_RawID(void) {
        while (1) {
            if (!this->_locked) {
                this->_locked = true;
                RawID r;
                r = RawID(this->_last);
                this->_last++;
                this->_locked = false;
                return r;
            }
        }

    }
};

} // XS_CORE
#endif // XS_CORE_RAWID__
