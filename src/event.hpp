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


#ifndef XS_CORE_EVENT__
#define XS_CORE_EVENT__

#include "include/mgr.hpp"

namespace xs_core {

class Event;

class EventMgr: protected MgrWithRID<Event, EventMgr> {
protected:
    void _add_item(Event &evt);
public:
    friend class Event;
    EventMgr() {}
    ~EventMgr() {}
    Event new_evt(void);
    void cleanup(void);
    inline bool operator==(EventMgr& rhs) {
        return this->rid == rhs.rid;}
};


class Event: public NamedOb<Event> {
// Note: only mgr class uses rawids
protected:
    EventMgr *_mgr;
    bool handled = false;
    //int _remaining = 0; // -1 is forever
public:
    Event(EventMgr &mgr) {
        mgr._add_item(*this);
    }
    ~Event() {}
    unsigned handle(void) {
        //if (!(this->_remaining == 0 && this->handled))
        if (!this->handled)
            this->handled = true;
            return 1;
        return 0;
    }
    bool is_handled(void) {return this->handled;}
    /*bool is_reoccuring(void) {return this->_remaining == 0;}
    int get_times_remaining(void) {return this->_remaining;}
    void set_times_remaining(const int t) {
    *   if (!this->handled)
    *       this->_remaining = (t <= -1) ? -1 : t;
    * }
    bool has_remaining(void) {return this->remaining == 0;}
    */
    bool _is_done(void) {
        return (this->handled);
        //return (this->_remaining == 0 && this->handled);
    }
    inline bool operator==(Event& rhs) {
        return (this->_mgr == rhs._mgr &&
                this->handled == rhs.handled &&
                this->name == rhs.name);
    }
};


//static MgrMgr<Event, EventMgr> eventmanagers = MgrMgr<Event, EventMgr>();

} // xs_core
#endif // XS_CORE_EVENT__
