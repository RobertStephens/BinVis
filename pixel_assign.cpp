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

#include "pixel_assign.h"

#include <iostream>

void PixelAssign::thresh(RGB& rgb, char point) {
 
    char all = 0xFF;
    if(point == 0x0) {
        rgb._r = 0x0;
        rgb._g = 0x0;
        rgb._b = 0x0;
        rgb._a = 0xFFFF;
    }
    else if(point == all) {
        rgb._r = 0xFFFF;
        rgb._g = 0xFFFF;
        rgb._b = 0xFFFF;
        rgb._a = 0xFFFF;
    }
    else {
        rgb._r = (0xFF*static_cast<unsigned char>(point) );
        rgb._g = 0x7777;
        rgb._b = 0xFFFF - rgb._r;
        
        /*int a = (0xFFFF)/2 - rgb._b;
        if(a < 0) a = 0 - a;
        rgb._a = a + (0xFFFF)/2;*/
       
        rgb._a = 0xFFFF;

        /* std::cout << rgb._r << " " << rgb._b << " " << 
                     static_cast<unsigned char>(point) << " " << rgb._a << std::endl; */
        
    }
}

