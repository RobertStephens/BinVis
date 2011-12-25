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


#ifndef PIXEL_GENERATOR_H_
#define PIXEL_GENERATOR_H_

#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>
#include <string>

#include "./png++/png.hpp"

#include "RGB_point.h"

class PixelGenerator {

public:
    PixelGenerator(size_t width, size_t height, std::vector<std::vector<RGB> >& _image_data);

    int write(std::string image_filename);

private:
   
    png::image< png::rgba_pixel > _image;

};

#endif /* PIXEL_GENERATOR_H_ */

