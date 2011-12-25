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


#include "hilbert.h"

using namespace std;

Hilbert::Hilbert(int n, int usable_length) : 
    _n(n), 
    _usable_length(usable_length), _image_data(_n, vector<RGB>(_n) ) { 
}


int Hilbert::run(char* data, PixelAssign& pixel_assign) {

    int x, y;

    for(int d = 0; d < _usable_length; ++d) {
        d2xy(_n, d, x, y);
        pixel_assign.thresh(_image_data[x][y], data[d]); 
    }

}


int Hilbert::write_image(string image_filename) {

    try {

        PixelGenerator pixel_generator(_n, _n, _image_data);
        pixel_generator.write(image_filename); 
    
    }
    catch (std::exception const& error) {
        std::cerr << "PixelGenerator: " << error.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}

//convert (x,y) to d
int Hilbert::xy2d(int n, int x, int y) {
    int rx, ry, s, d=0;
    for (s=n/2; s>0; s/=2) {
        rx = (x & s) > 0;
        ry = (y & s) > 0;
        d += s * s * ((3 * rx) ^ ry);
        rot(s, x, y, rx, ry);
    }
    return d;
}
 
//convert d to (x,y)
void Hilbert::d2xy(int n, int d, int& x, int& y) {
    int rx, ry, s, t=d;
    x = y = 0;
    for (s=1; s<n; s*=2) {
        rx = 1 & (t/2);
        ry = 1 & (t ^ rx);
        rot(s, x, y, rx, ry);
        x += s * rx;
        y += s * ry;
        t /= 4;
    }
}
 
//rotate/flip a quadrant appropriately
void Hilbert::rot(int n, int& x, int& y, int rx, int ry) {
    int t;
    if (ry == 0) {
        if (rx == 1) {
            x = n-1 - x;
            y = n-1 - y;
        }
        t = x;
        x = y;
        y = t;
    }
}
