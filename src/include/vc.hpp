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


#ifndef XS_CORE_VC__
#define XS_CORE_VC__

#include <iostream>
#include <vector>

namespace XS_CORE {

template <class ITEM_T, class CLS_T>
class VC { // Vector container class
protected:
    virtual ~VC();
    std::vector<ITEM_T> items;
    void _del_item(ITEM_T item) {this._del_item_by_idx(this->indexof(item));}
    void _del_item_by_idx(const unsigned i) {
        if (i == 0 || i <= this->size())
            this->items.erase(this->items.begin()+i);
    }
    void _add_item(ITEM_T &item) {this->items.push_back;}
public:
    inline unsigned size(void) const {return this->items.size();}
    inline bool is_empty(void) {return this->items.size() == 0;}
    size_t indexof(ITEM_T item) {
        // returns -1 if item does not exist
        const unsigned s = this->items.size();
        for (unsigned i=0; i<s; i++)
            if (this->items[i] == item) return i;
        return -1;
    }
    bool has_item(ITEM_T item) {
        const unsigned s = this->items.size();
        for (unsigned i=0; i<s; i++)
            if (this->items[i] == item) return true;
        return false;
    }
    bool operator==(const CLS_T &rhs) {return this->items->operator==(rhs);}
    bool operator!=(const CLS_T &rhs) {return !this->operator==(rhs);}
    ITEM_T& operator[](size_t i) {return this->items[i];}
    const ITEM_T& operator[](size_t i) const {return this->items[i];}
};

} // XS_CORE
#endif // XS_CORE_VC__
