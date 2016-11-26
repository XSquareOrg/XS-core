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


#ifndef XS_CORE_STATEPROPS__
#define XS_CORE_STATEPROPS__

#include "stateops_T.hpp"
#include "../utils/clamp.hpp"

namespace xs_core {

template <typename NUM, class T>
class state_switch_T: public stateops_T<NUM, T> {
    /* Basic state machine switch
     * Note NUM must be a form of int eg. unsigned, long, etc.
     */
protected:
    NUM min, max;
public:
    virtual ~state_switch_T();
    const NUM get(void) const {return this->state;}
    NUM get(void) {return this->state;}
    inline int set(const NUM state) {
        // returns 1 if changed, -1  out of bounds, 0 if no change
        if (this->state == state) return 0; // no change
        else if (this->min <= state || state <= this->max)
            this->state = state;
            return 1; // changed
        return -1; // out of bounds -- no change
    }
    inline int set_clamped(const NUM state) {
        // returns 1 if changed, otherwise 0
        if (state == this->state) return 0; // no change
        else this->state = clamped(state, this->min, this->max);
        return 1; // changed
    }
    inline void operator++(void) {
        if (this->state < this->max) this->state++;
    }
    inline void operator--(void) {
        if (this->state > this->min) this->state--;
    }
};


template <typename NUM, class T>
class looping_state_switch_T: public state_switch_T<NUM, T> {
    /*
     * Note NUM must be a form of int eg. unsigned, long, etc.
     */
protected:
    NUM min, max;
public:
    virtual ~looping_state_switch_T();
    inline void operator++(void) {
        (this->state == this->max) ? this->state = this->min : this->state++;
    }
    inline void operator--(void) {
        (this->state == this->min) ? this->state = this->max : this->state--;
    }
};


template <typename NUM>
class _state_switch_with_default_mixin {
    // Mixin class to add a default state to state_switch classes
protected:
    NUM _default_state;
public:
    inline NUM &default_state(void) {return this->_default_state;}
    inline bool is_default(void) {return this->_default_state == this->state;}
    inline void clear(void) {this->state = this->_default_state;}
};


// Supplimentary Classes with default
template <typename NUM, class T>
class state_switch_with_default_T:
        public _state_switch_with_default_mixin<NUM> {
};


template <typename NUM, class T>
class looping_state_switch_with_default_T:
    public _state_switch_with_default_mixin<NUM> {
};


} // xs_core
#endif // XS_CORE_STATEPROPS__
