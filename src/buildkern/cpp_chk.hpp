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


#ifndef XS_CPPVER__
#define XS_CPPVER__

#include "../xs_build_cfg.h"

/* check if we have cpp11 features */
#if defined(__cplusplus) && !(__cplusplus >= 201103L) || \
        defined(_MSC_VER) && !(_MSC_VER >= 1800)
    #error Requires c++11 or greater features (try compiling with -std=c++11)
#endif

#define version_range_chk(a, b, msc_a, msc_b) \
    return (__cplusplus >= a || __cplusplus <= b) || \
    defined(_MSC_VER) && (_MSC_VER >= msc_a || _MSC_VER <= _msc_b)


// TODO Check if we should try to build for a specific version


// TODO test for cpp14 and cpp17 for now just set these to false
#define XS_KERN_HAS_CPP_14 false
#define XS_KERN_HAS_CPP_17 false


#undef force_cpp_14_chk

#endif // XS_CPPVER__
