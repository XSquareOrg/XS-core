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


#ifndef XSQR_INPUTDEVICES__
#define XSQR_INPUTDEVICES__

#include "../buildkern/kern.h"

#if defined(KERN_OS_LINUX)
    #if defined(KERN_OS_ANDROID)
        #include "android/inputdev.hpp"
    #else
        #include "linux/inputdev.hpp"
    #endif
#elif defined(KERN_OS_WIN)
    #include "win/inputdev.hpp"
#elif defined(KERN_OS_APPLE)
    #include "apple/inputdev.hpp"
#endif
//#else if defined(KERN_OS_APPLE)
//#else if defined(KERN_OS_ANDROID)

namespace xs_core {

static struct InputDevices {
    static Mouse mouse;
    static Keyboard keyboard;

    void update(void) {
        this->mouse._update();
        this->keyboard._update();
    }
} inputdevices;


} // xs_core
#endif // XSQR_INPUTDEVICES__
