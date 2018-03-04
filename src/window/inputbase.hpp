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


#ifndef XS_CORE_INPUTBASE__
#define XS_CORE_INPUTBASE__

#include "../vec/vec2.hpp"
#include <utility>

namespace xs_core {

class _Mouse {
protected:
    Vec2i pos;
    struct {bool l, r, m;} pressed;
    struct {int lr, ud;} scrolled;

public:
    virtual void _update(void);

    Vec2i position(void) {return this->pos;}
    // button pressed

    bool has_pressed(void) {
        return (this->pressed.l || this->pressed.r || this->pressed.m);
    }

    bool left_ispressed(void) {return this->pressed.l;}

    bool right_ispressed(void) {return this->pressed.r;}

    bool middle_ispressed(void) {return this->pressed.m;}

    // scroll
    bool any_scrolled(void) {
        return this->scrolled.ud != 0 || this->scrolled.lr != 0;
    }

    bool is_scrolled_left(void) {return this->scrolled.lr == -1;}

    bool is_scrolled_right(void) {return this->scrolled.lr == 1;}

    bool is_scrolled_up(void) {return this->scrolled.ud == -1;}

    bool is_scrolled_down(void) {return this->scrolled.ud == 1;}
};


struct KbdMods{
    bool shift=false;
    bool ctrl=false;
    bool alt=false;

    bool any_pressed(void) {return (this->shift || this->ctrl || this->alt);}
};



class KeyState {
    unsigned count = 0;
    struct k {} kp;
public:
    friend void swap(KeyState& a, KeyState& b) {
        std::swap(a.kp, b.kp);
        std::swap(a.count, b.count);
    }
    KeyState& operator=(KeyState other) {
        swap(*this, other);
        return *this;
    }
    KeyState& operator=(const KeyState& other) {
        KeyState tmp(other);
        swap(*this, tmp);
        return *this;
    }
    unsigned pressed_count(void) {return this->count;}
    bool any_pressed(void) {return this->count;}
    bool operator==(const KeyState &rhs);;
    bool operator!=(const KeyState &rhs) {return !this->operator==(rhs);}
};


class _Keyboard {
protected:
    KeyState ks;
    KbdMods left, right; // modifiers
    void _clear_state(void);

public:
    &operator const KeyState() const {return this->ks;}

    virtual void _update(void);

    bool any_pressed(void);

    // modifiers
    inline bool any_shift_pressed(void) {
        return this->left.shift || this->right.shift;
    }

    inline bool any_ctrl_pressed(void) {
        return this->left.ctrl || this->right.ctrl;
    }

    inline bool any_alt_pressed(void) {
        return this->left.alt || this->right.alt;
    }

    inline bool modifier_is_pressed(void) {
        return (this->left.any_pressed() || this->right.any_pressed());
    }

    bool operator==(const KeyState &rhs) {return this->ks == rhs;}
};


} // xs_core
#endif // XS_CORE_INPUTBASE__
