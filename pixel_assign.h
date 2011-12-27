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

#ifndef PIXEL_ASSIGN_H_
#define PIXEL_ASSIGN_H_

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>

#include "RGB_point.h"
#include "include/stringify.h"

class PixelAssign {

public:
    PixelAssign(void) {
    
        std::string config_file = "./config/config.txt";
        bool dump_results = true;
        parse_config(config_file, dump_results); 
    
    }
    
    int parse_config(std::string config_file, bool dump_results);

    void thresh(RGB& rgb, char point);

private:

    void dump_param_map(void);

    std::map<std::string, unsigned short> _param_map;

};

#endif /* PIXEL_ASSIGN_H_ */


