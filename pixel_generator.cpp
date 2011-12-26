/*   
 *  Copyright (c) 2011 Robert Stephens 
 *
 *  This file is part of BinVis.
 *
 *  BinVis is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  BinVis is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with BinVis.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <cstdlib>
#include <iostream>
#include <ostream>

#include "pixel_generator.h"

    
PixelGenerator::PixelGenerator(size_t width, size_t height, std::vector<std::vector<RGB> >& _image_data) :
    _image(width, height) {

    for (size_t y = 0; y < _image.get_height(); ++y) {
        for (size_t x = 0; x < _image.get_width(); ++x) {
            
            _image[y][x] = png::rgba_pixel(_image_data[x][y]._r, _image_data[x][y]._g, 
                                           _image_data[x][y]._b, _image_data[x][y]._a);
        }
    }
    
}

int PixelGenerator::write(std::string image_filename) {
    _image.write(image_filename.c_str() );

    return 0;
}
