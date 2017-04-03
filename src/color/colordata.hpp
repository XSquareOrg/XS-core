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

// Color data storage types
// Used to store color data for images and the like

#ifndef XS_CORE_COLORDATA_TYPES__
#define XS_CORE_COLORDATA_TYPES__

#include "color.hpp"

namespace xs_core {

struct DummyColData {
/* Note: must call a single instance (for each type that refs it)
 *  declared with static
 *  example -- static DummyColData _somename_here;
 */
private:
    unsigned _refcount = 0;
public:
    char colorspace(void) {return -1;}
    void incref(void) {this->_refcount++;}
    void decref(void) {this->_refcount--;}
};


#define _BWBLACK 0
#define _BWWHITE 1


struct BWData {
    // data is stored as 0s and 1s
    char colorspace(void) {return 0;}
};


struct NonColorData {
    // data is stored as single values from 0 (black) to 255 (white)
    char colorspace(void) {return 1;}
};


struct RGB8Data {
    char colorspace(void) {return 2;}
};


struct RGBA8Data {
    char colorspace(void) {return 2;}
};


struct RGB16Data {
    char colorspace(void) {return 3;}
};


struct RGBA16Data {
    char colorspace(void) {return 4;}
};


} // xs_core
#endif // XS_CORE_COLORDATA_TYPES
