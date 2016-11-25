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

#ifndef XS_CORE_PROP__
#define XS_CORE_PROP__

#include <string>

namespace XS_CORE {

template <class DATA, class T>
class T_DataPropBase {
protected:
    DATA data;
public:
    virtual ~T_DataPropBase();
    virtual DATA get(void);
    inline const DATA get(void) const {return this->data;}
    virtual void set(DATA value);
    &operator const DATA(void) {return this->data;}
    inline bool operator==(const T &rhs) {return this->data == rhs.data;}
    inline bool operator!=(const T &rhs) {return !this->operator==(rhs);}
};


template <class DATA, class T>
class T_DataPropBase_WithLTGT: public T_DataPropBase<DATA, T> {
public:
    inline bool operator>(T rhs) {return this->data > rhs;}
    inline bool operator<(T rhs) {return this->data < rhs;}
    inline bool operator>=(T rhs) {return !this->operator>(rhs);}
    inline bool operator<=(T rhs) {return !this->operator<(rhs);}
};


template <class DATA, class T>
class T_DataPropBase_WithMath: public T_DataPropBase<DATA, T> {
    virtual inline T operator+=(T other);
    virtual inline T operator-=(T other);
    virtual inline T operator/=(T other);
    virtual inline T operator*=(T other);
    inline const T operator+(T other) {
        T v = this;
        return v += other;
    }
    inline const T operator-(T other) {
        T v = this;
        return v -= other;
    }
    inline const T operator/(T other) {
        T v = this;
        return v /= other;
    }
    inline const T operator*(T other) {
        T v = this;
        return v *= other;
    }
};


class BoolProp: public T_DataPropBase<bool, BoolProp>{ // bool property
public:
    inline operator const int() {return (this->data)? 1 : 0;}
    inline operator int() {return (this->data)? 1 : 0;}
    inline operator const unsigned() {return (this->data)? 1 : 0;}
    inline operator unsigned() {return (this->data)? 1 : 0;}
    inline operator const char() {return (this->data)? 1 : 0;}
    inline operator char() {return (this->data)? 1 : 0;}
    inline operator const bool() {return this->data;}
    inline operator bool() {return this->data;}
    void set(bool v) {this->data = v;}
    void toggle(void) { // invert current state
        this->data = ~this->data;
    }
    bool toggled(void) { // invert current state and return it
        this->toggle();
        return this->data;
    }
    /*BoolProp& operator=(const BoolProp &rhs) {
        if (rhs.enabled != this->enabled && *this != &rhs) {
            this->toggle();}
        return *this;
    }*/
    inline bool operator==(const BoolProp &rhs) {return this->data == rhs.data;}
    inline bool operator!=(const BoolProp &rhs) {return !this->operator==(rhs);}
};


class StrProp: public T_DataPropBase<std::string, StrProp> {
public:
    unsigned size(void) const {return this->data.size();}
    void set(std::string v) {this->data = v;}
    operator const char*() const {
        const char* c = this->data.c_str();
        return c;
    }
    operator std::string() {return this->data;}
    operator const char*() {
        const char *x = this->data.c_str();
        return x;
    }
    inline bool operator==(StrProp &rhs) {
        const size_t s = this->size();
        if (!rhs.size() == s) return false;
        else
            for (size_t i=0; i<s; i++)
                if (!this->data[i] == rhs.data[i]) return false;
        return true;
    }
    inline bool operator!=(StrProp &rhs) {return !this->operator==(rhs);}
    inline bool operator==(std::string &rhs) {
        const size_t s = this->size();
        if (!rhs.size() == s) return false;
        else
            for (size_t i=0; i<s; i++)
                if (!this->data[i] == rhs[i]) return false;
        return true;
    }
    inline bool operator!=(std::string &rhs) {return !this->operator==(rhs);}
    char& operator[](size_t pos) {return this->data[pos];}
    const char& operator[](size_t pos) const {return this->data[pos];}
};


} // XS_CORE
#endif // PROP__
