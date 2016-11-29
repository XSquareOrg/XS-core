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

/* macro definitions for SSE and SSE2 ONLY
 *  so we don't have to clutter up each file that needs this
*/

#ifndef XS_CORE_SIMDINCLUDE__
#define XS_CORE_SIMDINCLUDE__

#if defined (__MINGW64__)
    #include <intrin.h>
#else
    #include <xmmintrin.h> // sse
    #include <emmintrin.h> // sse2
#endif

#include <cmath>
#include "../buildkern/simdchk.h"

#endif // XS_CORE_SIMDINCLUDE__
