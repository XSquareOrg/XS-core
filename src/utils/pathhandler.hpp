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

#ifndef XS_CORE_PATHHANDLER__
#define XS_CORE_PATHHANDLER__

#include <string>
#include <vector>
#include <cstdarg>

#if defined(_WIN32) || defined (__CYGWIN__)
    #define PATH_SEP '\\' // Windows
#else
    #define PATH_SEP '/' // Unix-like
#endif

namespace xs_core {


void contencate_path(std::string path, std::string suffix) {
    path += PATH_SEP;
    path += suffix;
}

std::string parent_dir(std::string path);

bool is_valid_path(std::string path);

bool is_file(std::string path); // True if path points to a file

bool is_dir(std::string path); // True if path points to a directory

std::vector<std::string> get_dir_contents(std::string path) {
    // return a std::vector with all subfiles and subdirs
    //  will be empty if path is empty or not a directory
    std::vector<std::string> d;
    return d;
}

std::vector<std::string> get_dir_subfiles(std::string path) {
    // return a std::vector with all subfiles and subdirs
    //  will be empty if path is empty or not a directory
    std::vector<std::string> d;
    //if is_dir(path)
    return d;
}

std::vector<std::string> get_dir_subdirs(std::string path) {
    // return a std::vector with all subfiles and subdirs
    //  will be empty if path is empty or not a directory
    std::vector<std::string> d;
    //if is_dir(path)
    return d;
}

int dir_has_subdir(std::string path) {
    // returns -1 if path is not a directory or if an error occurs
    if (is_dir(path))
        // TODO
        return 0;
    else return -1;
}

int dir_is_empty(std::string path) {
    // returns -1 if path is not a directory or if an error occurs
    if (is_dir(path))
        // TODO
        return 0;
    else return -1;
}


} // xs_core
#endif // XSCORE_PATHHANDLER__
