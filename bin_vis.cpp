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

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>

#include "hilbert.h"
#include "pixel_assign.h"
#include "include/stringify.h"

using namespace std;

//find smallest power of 2 less than root file size
int compute_file_params(string file_in, int& n, int& usable_length);

//obtain allowed amount of data from binary file
int obtain_data(string file_in, char* data, int usable_length);


int main(int argc, char** argv) {


    if(argc < 2) {
        cerr << "usage: ./bin_vis binary_in [image_out.png]" << endl;
        return EXIT_FAILURE;
    }

    string image_file;
    if(argc > 2) {
        image_file = argv[2];
    }
    else {
        image_file = "out.png";
    }

    int n, usable_length;
    string file_in = argv[1];
   
    int ret = compute_file_params(file_in, n, usable_length);
    if(ret != 0) {
        cerr << "IO Error: " << file_in << endl;
        return EXIT_FAILURE;
    }
    
    char* data = new char[usable_length];
    
    ret = obtain_data(file_in, data, usable_length);
    if(ret != 0) {
        cerr << "IO Error: " << file_in << endl;
        return EXIT_FAILURE;
    }

    int decimation = 1;
    int size_limit = 1024; 

    if(n > size_limit) {
        decimation = n / size_limit;
    }
   
    string decim_string = "using no decimation";
    if(decimation != 1) {
        decim_string = "using decimation factor of " + stringify(decimation);
    }
    cout << decim_string << endl;

    Hilbert hilbert(n/decimation, usable_length);

    PixelAssign pixel_assign; 
    
    hilbert.run(data, pixel_assign, decimation);
    delete[] data;
    
    ret = hilbert.write_image(image_file);
    if(ret != 0) {
        cerr << "Image writing error: " << image_file << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
//find smallest power of 2 less than root file size
int compute_file_params(string file_in, int& n, int& usable_length) {
ifstream in_file(file_in.c_str() );
    
    if( !in_file.is_open() ) {
        return -1;
    }

    in_file.seekg(0, ios::end);
    int length = in_file.tellg();
    in_file.close();

    
    double root_full = sqrt(length);
    double log2root_full = log2(root_full);

    int log2root = floor(log2root_full);
    int root = pow(2, log2root);
   
    /*cout << "root_full: " << root_full << ", "
         << "log2root_full: " << log2root_full << ", "
         << "root: " << root << ", "
         << "log2root: " << log2root << endl; */

    n = root;
    usable_length = root * root;
    
    cout << "n=" << n << ", usable_length=" << usable_length 
         << ", length=" << length 
         << ", percentage coverage=" << (100.0 * usable_length)/length << "%" << endl;

    return 0;
}


int obtain_data(string file_in, char* data, int usable_length) {

    ifstream in_file(file_in.c_str() );
    
    if( !in_file.is_open() ) {
        return -1;
    }
    
    in_file.read(data, usable_length);
    in_file.close();
    
    return 0;
}

