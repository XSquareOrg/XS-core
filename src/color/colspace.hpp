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

#ifndef XS_CORE_COLSPACE__
#define XS_CORE_COLSPACE__

namespace xs_core {

enum class color_space : char {
    NONE =          -1, // special case for de-referenced items
    BW =            0,
    NON_COLOR_8 =   1,
    RGB_8 =         2,
    RGBA_8 =        3,
    RGB_16 =        4,
    RGBA_16 =       5
};

bool color_space_has_alpha(char t) {return (t == 3 || t == 4);}

unsigned color_space_bitness(char t) {
    if (t == 0) return 1;
    else if (t <= 3) return 8;
    else return 16;
}


} // xs_core
#endif // XS_CORE_COLSPACE__
