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


#ifndef XS_CORE_GRADIENT__
#define XS_CORE_GRADIENT__

#include <vector>

namespace xs_core {

template <class COLOR>
struct GradientStop {
protected:
    unsigned offset;
public:
    COLOR color;
    unsigned get_offset(void) {return this->offset;}
    void set_offset(unsigned x) {this->offset= (x >= 100) ? 100 : x;}
    bool operator==(const GradientStop& rhs) {
        return (this->offset == rhs && this->color == rhs);
    }
    bool operator!=(const GradientStop& rhs) {
        return !this->operator==(rhs);
    }
};


template <class COLOR>
class Gradient {
protected:
    std::vector<GradientStop<COLOR>> items;
public:
    Gradient() {
    }
    ~Gradient();
    unsigned size(void) {return this->items.size();}
    GradientStop<COLOR> add_stop(void);
    GradientStop<COLOR> add_stop_to_end(void);
    void delete_stop(unsigned index);
};


} // xs_core
#endif // XS_CORE_GRADIENT__
