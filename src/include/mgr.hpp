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


#ifndef XS_CORE_MGR__
#define XS_CORE_MGR__

#include "vc.hpp"
#include "rawid.hpp"
#include "prop.hpp"

namespace XS_CORE {

// TODOs (as needed)
// 1 -- make Mgrs more universaly compatable with other std container types
// 2 -- Thread safety?

template <class ITEM, class T>
class Mgr: public VC<ITEM, T> {
protected:
public:
    virtual ~Mgr();
    void _add_item(ITEM &item) {this->items.push_back(*item);}
};


template <class ITEM, class T>
class MgrWithRID: public Mgr<ITEM, T> {
// Only the manager (T) uses an rid
// - Comparisons are done using rids for speed
protected:
    MgrRawID &rid;
    const unsigned &ID(void) const {return &this->rid.ID();}
public:
    virtual ~MgrWithRID();
    inline bool operator==(T& rhs) {return this->rid == rhs.rid;}
};


template <class ITEM, class T> // ITEM must inherit from ObWithRID
class ObWithRID_MgrWithRID: public MgrWithRID<ITEM, T> {
// Both the manager (T) and the items it manages (ITEM) use rids
protected:
    void _add_item(ITEM &item) {
        item.rid = this->rid.new_RawID();
        this->items.push_back(*item);
    }
public:
    virtual ~ObWithRID_MgrWithRID();
    inline bool operator==(T& rhs) {return this->rid == rhs.rid;}
};


template <class ITEM, class T>
class MgrMgr: public Mgr<ITEM, T> {
// manager to manage 'managers'
// the item ('manager') to be managed (ITEM) MUST inherit from
//      MgrWithRID or one of its derived classes
//      OR use utilize an rid in the same manner as MgrWithRID
// - Comparisons are done using RIDS for speed
public:
    virtual ~MgrMgr();
    const T get_mgr_by_MGRID(const unsigned id) {
        for (unsigned i=0; i<this->size; i++)
            if (this->items[i].rid == id) return this->items[i];
    }
    const T get_mgr(const ITEM &item) {
        return this->get_mgr_by_MGRID(item._mgrid);
    }
};


/* ---- Primative Object types ---------------------------------------------- */
template <class T>
class _Ob_BC { // Base class
public:
    virtual ~_Ob_BC();
    T& operator=(const T &other) { //copy
        if (this != &other) return *this;
    }
    T& operator=(T &other) { // move
        if (this != &other) return *this;
    }
    virtual bool operator==(T &rhs);
    bool operator!=(T &rhs) {return !this->operator==(rhs);}
};


template <class T>
class NamedOb: public _Ob_BC<T> {
public:
    StrProp name;
    virtual ~NamedOb();
};


template <class T>
class ObWithRID: public _Ob_BC<T> {
protected:
    RawID &rid;
    const unsigned &ID(void) {return this->rid.ID();}
public:
    ObWithRID();
    virtual ~ObWithRID();
    T& operator=(const T &other) { // copy
        if (this != &other) {// must increment rid
            T x = *this;
            x.rid = this->rid.new_RawID();
            return x;
        } else return *this;
    }
    // Exact ==/!= comparison only with rids!!
    bool operator==(const T &rhs) {return this->rid == rhs.rid;}
};


template <class T>
class NamedObWithRID: public ObWithRID<T> {
public:
    StrProp name;
    virtual ~NamedObWithRID();
    const std::string name_with_rid_suffix(const char sep) {
        std::string r = std::to_string(this->rid);
        return   name + sep + this.rid;
    }
};

} // XS_CORE
#endif // XS_CORE_MGR__
