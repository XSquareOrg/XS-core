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

#ifndef XS_CORE_ANGLEFUNCS__
#define XS_CORE_ANGLEFUNCS__

#include "pi_const.hpp"

namespace XS_CORE {

template <typename T>
inline T deg_to_rads(const T n) {return n*PI_OVER_180;}

template <typename T>
inline T rads_to_deg(const T n) {return n*PI_UNDER_180;}

}; // XS_CORE
#endif // XS_CORE_ANGLEFUNCS__
