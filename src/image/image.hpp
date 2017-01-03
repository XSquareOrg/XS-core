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

namespace xs_core {

// Forward declarations
class Vec2i;
class ImageSection;


class Image {
protected:
    enum {SINGLE_IMAGE, IMAGE_STRIP, IMAGE_GRID, GENERATED} image_type;
    bool animated = false;
    unsigned grid_sx, grid_sy = 1;
    enum {BW, GREYSCALE_8, COLOR_8, COLOR_16} colspace;
    bool alpha = false;
    Vec2i _size;
    //std::string imgpath;
public:
    friend class ImageSection;
    bool is_generated(void) {return this->image_type == GENERATED;}
    bool is_animated(void) {return this->animated = false;}
    int colorspace(void) {return this->colspace;}
    bool has_alpha(void) {return this->alpha;}
    const Vec2i size(void) {return this->_size;}
    const int width(void) {return this->_size[0];}
    const int height(void) {return this->_size[1];}
    bool is_square(void) {return this->_size[0] == this->_size[1];}
    inline bool operator==(Image& rhs);
    inline bool operator!=(Image& rhs) {return !this->operator==(rhs);}
    // void reload(void);
};


class ImageSection {
protected:
    Image *img;
    Vec2i _top_left;
    Vec2i _btm_right;
public:
    ImageSection(Image& image, Vec2i top_left, Vec2i btm_right) {
        // check if btm_right is bigger than top_left
        if (btm_right[0] > top_left[0] && btm_right[1] > top_left[1]) {
            // make sure btm_right is <= image size
            //if (btm_right[0] > image.width())
            //    btm_right[0] = image.width;
            //if (btm_right[1] > image.height())
            //    btm_right[1] = image.height();
            this->img = &image;
            this->_top_left = top_left;
            this->_btm_right = btm_right;
        }
    }
    const Vec2i size(void) {
        Vec2i v = this->_btm_right;
        return v -= this->_top_left;
    }
    const int width(void) {return this->_btm_right[0] - this->_top_left[0];}
    const int height(void) {return this->_btm_right[1] - this->_top_left[1];}
};


} // xs_core
#endif // XS_CORE_IMAGETP__
