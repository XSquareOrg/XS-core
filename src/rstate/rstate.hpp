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

#ifndef XS_CORE_RSTATE__
#define XS_CORE_RSTATE__

#include "stateops_T.hpp"

namespace XS_CORE {

namespace RUNSTATES {
    const char INVALID = -99;
    const char ENDED = -2;
    const char INIT = -1;
    const char NOT_STARTED = 0;
    const char RUNNING = 1;
    const char MIN_STATE = ENDED;
    const char MAX_STATE = RUNNING;
}

namespace RSNAMES {
    const char* INVALID = "invalid";
    const char* ENDED = "ended";
    const char* INIT = "init";
    const char* NOT_STARTED = "not started";
    const char* RUNNING = "running";
}

const char*& get_rsname(const char s) {
    switch(s) {
        case RUNSTATES::ENDED:          return RSNAMES::ENDED;
        case RUNSTATES::INIT:           return RSNAMES::INIT;
        case RUNSTATES::NOT_STARTED:    return RSNAMES::NOT_STARTED;
        case RUNSTATES::RUNNING:        return RSNAMES::RUNNING;
    }return RSNAMES::INVALID;
}


class RState: public stateops_T<char, RState> {
protected:
    char state = 0;
    void _set_state(const char state) {this->state = state;}
public:
    virtual ~RState();
    char get_state(void) {return this->state;}
    const char get_state(void) const {return this->state;}
    const char* get_state_name(void) {return get_rsname(this->state);}
    bool is_started(void) {return this->state > 0;}
    bool is_init(void);
    bool is_running(void);
    bool is_ended(void);
    operator const char() {return this->state;}
    operator char() {return this->state;}
};

} // XS_CORE
#endif // XS_CORE_RSTATE__
