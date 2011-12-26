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

#ifndef HILBERT_H_
#define HILBERT_H_

#include <iostream>
#include <vector>

#include "pixel_assign.h"
#include "RGB_point.h"

#include "pixel_generator.h"

class Hilbert {


public:

    Hilbert(int n, int usable_length);

    int run(char* data, PixelAssign& pixel_assign, int decimation);

    int write_image(std::string image_filename);

private:

    //convert (x,y) to d
    int xy2d(int n, int x, int y);
 
    //convert d to (x,y)
    void d2xy(int n, int d, int& x, int& y);
 
    //rotate/flip a quadrant appropriately
    void rot(int n, int& x, int& y, int rx, int ry);

    int _n;
    int _usable_length; 
    std::vector<std::vector<RGB> > _image_data;
};

#endif /* HILBERT_H_ */
