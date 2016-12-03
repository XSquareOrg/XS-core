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


#ifndef XS_CORE_MAT3_AVX512__
#define XS_CORE_MAT3_AVX512__

// AVX512 version
namespace xs_core {


template <typename NUM, class T>
class Mat3Base {
public:
    const unsigned width(void) {return 3;}
    const unsigned height(void) {return 3;}
    bool is_square(void) {return true;}
    inline T operator+(const T& rhs) {
        T t;
        t.u.data.v += rhs.u.data.v;
        return t;
    }
    inline T operator-(const T& rhs) {
        T t;
        t.u.data.v -= rhs.u.data.v;
        return t;
    }
    inline T operator*(const NUM rhs) { // scalar product
        T t;
        t.u.data.v *= rhs.u.data.v;
        return t;
    }
    inline T operator*(const T& rhs) { // matrix product
        T t;
        t.u.data.v *= rhs.u.data.v;
        return t;
    }
};


class Mat3i: public Mat3Base<int, Mat3i> { // 3x3 int
public:
    inline Mat3i operator+=(const Mat3i& rhs);
    inline Mat3i operator-=(const Mat3i& rhs);
    inline Mat3i operator*=(const int rhs);
    inline Mat3i operator*=(const Mat3i& rhs);
};


class Mat3f: public Mat3Base<float, Mat3f> { // 3x3 float
public:
    inline Mat3f operator+=(const Mat3f& rhs);
    inline Mat3f operator-=(const Mat3f& rhs);
    inline Mat3f operator*=(const float rhs);
    inline Mat3f operator*=(const Mat3f& rhs);
};



} // xs_core
#endif // XS_CORE_MAT3_AVX512__
