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

#ifndef XS_CORE_IMAGETP__
#define XS_CORE_IMAGETP__

#include "../vec/vec2.hpp"
#include "../color/colspace.hpp"
#include "../color/colordata.hpp"

namespace xs_core {

// Forward declarations
class Vec2i;
class ImageSection;

enum class img_type {SINGLE_IMAGE, IMAGE_STRIP, IMAGE_GRID};

static DummyColData _dummy_imgcol_data;


class Image {
protected:
    img_type imgtype;
    bool animated = false;
    /* grid size
    * defaults to 1 (default is used for single_image)
    * for image strip one axis must set to 1 (otherwise will be considered
    *   an image grid)
    */
    unsigned grid_sx, grid_sy = 1;
    Vec2i _size;
    //std::string imgpath;

    /* ---- color space ----------------------- */
    char colspc = -1;
    union {                     // color_space
        DummyColData a;              // -1
        BWData b;               // 1
        NonColorData c;         // 2
        RGB8Data d;      // 3
        RGBA8Data e;     // 4
        RGB16Data f;     // 5
        RGBA16Data g;    // 6
    } data;

    /*template <class T>
    T& _active(void) {
        switch (this->colspc) {
            case 0: return this->data.b;
            case 1: return this->data.c;
            case 2: return this->data.d;
            case 3: return this->data.e;
            case 4: return this->data.f;
            case 5: return this->data.g;
            default: return this->data.a;
        }
        return -1; // error
    }*/

    template <class T>
    void _assign_color_data(T color_data) {
        if (this->colspc == 1) {
            if (color_data.colorspace != 1)
                // Replacing a DummyColData with a different type
                _dummy_imgcol_data.decref();
                _assign_color_data(color_data);
        }    // else do nothing
        else
            this->_deref_active();
            _assign_color_data(color_data);
    }

    void _deref(void) {
        // deref active and set active to DummyCol
        if (this->colspc != -1) // make sure were not already de-referenced
            this->_deref_active();
            this->colspc = -1;
            this->data.a = _dummy_imgcol_data;
            _dummy_imgcol_data.incref();
    }

private:
    void _deref_active(void); // TODO

    template <class T>
    void _assign_data(T color_data) {
        switch (color_data.colorspace) {
            case 0: this->data.b = color_data;
            case 1: this->data.c = color_data;
            case 2: this->data.d = color_data;
            case 3: this->data.e = color_data;
            case 4: this->data.f = color_data;
            case 5: this->data.g = color_data;
            default: this->data.a = color_data;
        }
        this->colspc = color_data.colorspace();
    }
    /* ---------------------------------------- */
public:
    //friend class ImageSection;
    //bool is_generated(void) {return this->img_type == GENERATED;}
    bool is_animated(void) {return this->animated = false;}
    int colorspace(void) {return this->colspc;}
    bool has_alpha(void) {return color_space_has_alpha(this->colspc);}
    const Vec2i size(void) {return this->_size;}
    const int width(void) {return this->_size[0];}
    const int height(void) {return this->_size[1];}
    bool is_square(void) {return this->_size[0] == this->_size[1];}
    bool size_is_pow_of_2(void);
    inline bool operator==(Image& rhs);
    inline bool operator!=(Image& rhs) {return !this->operator==(rhs);}
    // void reload(void);
};


} // xs_core
#endif // XS_CORE_IMAGETP__
