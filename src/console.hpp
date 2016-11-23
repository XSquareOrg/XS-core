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


#ifndef XS_CONSOLE__
#define XS_CONSOLE__


#include <string>
#include <iostream>
#include <vector>
#include "timestamp.hpp"

namespace XS_CORE {


namespace MSGTYPES {
    const char INFO = 0;
    const char WARN = 1;
    const char ERROR = 2;
    const char SEPARATOR = 10;
}


class Message {
protected:
    char msgtype;
    std::string msg;
    TimeStamp ts;
public:
    Message(const char msgtype, const std::string message) {
        this->ts = (*new TimeStamp());
        this->msgtype = msgtype;
        this->msg = message;
    }
    ~Message() {}
    const TimeStamp &timestamp(void) {return this->ts;}
    inline std::string as_log_formatted_string(void) {
        const std::string m = std::to_string(msgtype) + this->msg;
        return m;
    }
    inline bool operator==(const Message &rhs) {
        return (this->msgtype == rhs.msgtype &&
                this->msg == rhs.msg); //&& this->ts == rhs.ts);
    }
    inline bool operator!=(const Message &rhs) {return !this->operator==(rhs);}
};


class Console {
protected:
    std::vector<Message> items;
    void append(const Message &msg);
public:
    const unsigned size(void) const {return this->items.size();}
    const TimeStamp &last_timestamp(void) {return this->items.back().timestamp();}
    const Message &last(void) {return this->items.back();}
    void log(const char msgtype, const std::string msg) {
        if (msg.size() > 0) this->append((*new Message(msgtype, msg)));
        else if (msgtype == MSGTYPES::SEPARATOR) this->add_seperator();
    }
    void log_and_print(const char msgtype, const std::string msg) {
        if (msg.size() > 0) {
            this->append((*new Message(msgtype, msg)));
            std::cout << msg;
        } else if (msgtype == MSGTYPES::SEPARATOR) this->add_seperator();
    }
    void add_seperator(void) {
        this->append((*new Message(MSGTYPES::SEPARATOR, "")));
    }
    Message &operator[] (unsigned i) {
        if (i < 0) i = this->size() - i;
        if (i < 0 || i > this->size()) std::cout << "index is out of bounds.";
        else return this->items[i];
    }
    const Message &operator[] (unsigned i) const {
        if (i < 0) i = this->size() - i;
        if (i < 0 || i > this->size()) std::cout << "index is out of bounds.";
        else return this->items[i];
    }
};

} // XS_CORE
#endif // XS_CONSOLE__
