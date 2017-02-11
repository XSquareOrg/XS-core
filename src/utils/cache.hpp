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


#ifndef XS_CORE_CACHE__
#define XS_CORE_CACHE__

#include <vector>
#include <cstdlib>

namespace xs_core {


template <class T>
struct cache {
protected:
    std::vector<T> items;
    unsigned clean_interval = 60;
    bool paused = true;
public:
    size_t size(void) {return this->items.size();}
    bool is_empty(void) {return this->items.empty();}
    void cleanup(void);
    unsigned get_cleanup_interval(void) {return this->clean_interval;}
    void set_cleanup_interval(unsigned i) {
        this->clean_interval = (i <= 60) ? 60 : i;
    }
    // when paused cleanup wont be called. useful for hand optomizing
    bool cleanup_poll_is_paused(void) {return this->paused;}
    void pause_cleanup_poll(void) {this->paused = true;}
    void unpause_cleanup_poll(void) {this->paused = false;}
};


} // xs_core
#endif // XS_CORE_CACHE__
