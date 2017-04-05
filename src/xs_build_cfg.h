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


#ifndef XS_BUILD_CFG__
#define XS_BUILD_CFG__


/* -------------------------------------------------------------------------- */


// Uncomment one or more of these to force a specific version of c++ for
// XS core to compile with
//  if multiples are enabled then the highest version takes priority
// Note: this currently does nothing until c++ 14/ c++ 17 features are implemented
//#define XS_KERN_FORCE_CPP_11
//#define XS_KERN_FORCE_CPP_14
//#define XS_KERN_FORCE_CPP_17


// Uncomment this to force use of SSE features even if avx features are available
//#define XS_KERN_FORCE_SSE

#endif // XS_BUILD_CFG__
