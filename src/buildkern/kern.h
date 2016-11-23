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

#ifndef XS_KERN__
#define XS_KERN__
#ifdef __cplusplus
extern "C" {
#endif

/* Get a hint about what os were using and make sure were using a compatable OS
    -1 - unsupported
    0 - windows
    1 - mac
    2 - linux
    3 - android
    4 - other
*/

#ifdef __APPLE__
    #ifndef __MACH__
        #define __KERN_OS_APPLE
        #define __KERN_OS 1
    #else
        #define __KERN_OS -1 // os 9
        #define _KERN_OS_DEBUG = OS9
    #endif
#endif

#ifdef __linux__
    // TODO make sure were running a fairly recent kernel 2.6+ (or something?)
    #define __KERN_OS_LINUX
    #ifndef __ANDROID__
        #define __KERN_OS 2 // linux
    #else
        #define __KERN_OS_ANDROID
        #define __KERN_OS 3 // android (linux)
    #endif
#endif

#ifdef _WIN32
    // TODO check that were using windows 7 or greater
    #define __KERN_OS_WIN
    #define __KERN_OS 0
#endif

#ifndef __KERN_OS
/*#   define __KERN_OS 4
 TODO other
*/
    #define __KERN_OS -1
#endif

#if (__KERN_OS == -1)
    #error Unsupported OS or OS version.
#endif

#undef __KERN_OS

/* bitness */
#if defined(__ppc64__) || defined(__PPC64__) || defined(__x86_64__) || defined(__ia64__) || defined(_M_X64)
#   define __KERN_64_BIT__
#else
#   error Requires a 64bit (or greater) system.
#endif



#ifdef __cplusplus
}
#endif
#endif // XS_KERN__
