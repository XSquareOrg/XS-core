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


#ifndef TIMESTAMP__
#define TIMESTAMP__

#include <string>
#include <ctime>
#include <iostream>

namespace XS_CORE {

const char XS_TIME_FMT[20] = "%Y %d %h %D:%M:%S%p";

class TimeStamp {
protected:
    time_t ts;
    static char ts_fmt[30];
public:
    TimeStamp() {
        struct tm * timeinfo;
        char buffer[80];
        time(&this->ts);
        timeinfo = localtime(&this->ts);
        this->ts = strftime(buffer, 80, this->ts_fmt, timeinfo);
    }
    //const char to_char(void);
    const std::string to_string(void) const {return ctime(&this->ts);}
    std::string to_string(void) {return ctime(&this->ts);}
    inline bool operator==(const TimeStamp &rhs) {return this->ts == rhs.ts;}
    inline bool operator!=(const TimeStamp &rhs) {return !this->operator==(rhs);}
};


class TimeStampProfile {
protected:
    TimeStamp &start;
    TimeStamp &end;
public:
    TimeStampProfile();
    const TimeStamp start_stamp(void) {return this->start;}
    const TimeStamp end_stamp(void) {return this->end;}
    //time_t difference(void);
};

} // XS_CORE
#endif // TIMESTAMP__
