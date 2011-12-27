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

using namespace std;

int PixelAssign::parse_config(std::string config_file, bool dump_results) {

    ifstream infile( config_file.c_str() );

    std::string key, tmp;
    double value;

    if(!infile.is_open() ) {
        cerr << "unable to open file " << config_file << endl;
        return -1; 
    }

    size_t buff_size = 256;
    char tmp_buff[256];

    while( infile.getline(tmp_buff, buff_size) ) {

        tmp = string(tmp_buff);
        istringstream iss(tmp);

        vector<string> tokens;
        copy(istream_iterator<string>(iss),
             istream_iterator<string>(),
             back_inserter<vector<string> >(tokens));

        if(tokens.size() < 2 || tokens[0][0] == '#') {
            continue;
        }

        key = tokens[0];
        value = convertTo<unsigned short>(tokens[1]);
        _param_map[key] = value;
        //cout << key << " " << value << " "  << tokens[1]  << endl; 
    }

    if(dump_results) {
        dump_param_map();
    }

    return 0;
}

void PixelAssign::thresh(RGB& rgb, char point) {
 
    char all = 0xFF;
    if(point == 0x0) {
        rgb._r = 0x0;
        rgb._g = 0x0;
        rgb._b = 0x0;
        rgb._a = 0xFF;
    }
    else if(point == all) {
        rgb._r = 0xFF;
        rgb._g = 0xFF;
        rgb._b = 0xFF;
        rgb._a = 0xFF;
    }
    else {
        
        rgb._r = 0x00;
        rgb._g = 0x00;
        rgb._b = 0x00;

        //std::cout << std::hex << int( static_cast<unsigned char>(point) ) << std::endl;
        if( _param_map["blue_low"] <= static_cast<unsigned char>(point) && 
            _param_map["blue_high"] >= static_cast<unsigned char>(point) 
          ) {
            rgb._b = _param_map["intensity"] * (static_cast<unsigned char>(point) - _param_map["blue_low"])
                     / (_param_map["blue_high"] - _param_map["blue_low"] );
        }
        else if( _param_map["green_low"] <= static_cast<unsigned char>(point) && 
            _param_map["green_high"] >= static_cast<unsigned char>(point) 
          ) {
            rgb._g = _param_map["intensity"] * (static_cast<unsigned char>(point) - _param_map["green_low"])
                     / (_param_map["blue_high"] - _param_map["blue_low"] );
        }
        else if( _param_map["red_low"] <= static_cast<unsigned char>(point) && 
            _param_map["red_high"] >= static_cast<unsigned char>(point) 
          ) {
            rgb._r = _param_map["intensity"] * (static_cast<unsigned char>(point) - _param_map["red_low"])
                     / (_param_map["blue_high"] - _param_map["blue_low"] );
        
            /*cout << rgb._r << " " << static_cast<unsigned char>(point) << " "
                 << (static_cast<unsigned char>(point) - _param_map["red_low"]) << endl;*/
        }
        else {
            std::cout << "ERROR: " << std::endl;
        
        
        }

        rgb._a = _param_map["alpha"];

    }
}

void PixelAssign::dump_param_map(void) {
    std::map<std::string, unsigned short>::const_iterator it;
    for(it = _param_map.begin(); it != _param_map.end(); ++it) {
        std::cout << it->first << " " << std::hex << it->second << std::endl;
    }
}
