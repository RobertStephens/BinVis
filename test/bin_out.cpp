#include <iostream>
#include <fstream>

using namespace std;


int set_array(char* points, size_t arr_len, char value, string mode="default");

int main(void) {

    ofstream ofile("1out.bin");

    size_t arr_len = 1024;
    char* points = new char[arr_len];

    set_array(points, arr_len, -1);

    for(size_t i = 0; i < arr_len; ++i) {
        ofile.write(points, arr_len);
        set_array( points, arr_len, static_cast<char>(i) );
    }

    ofile.close();

    ofile.open("2out.bin");
    for(size_t i = 0; i < arr_len; ++i) {
        ofile.write(points, arr_len);
        set_array( points, arr_len, static_cast<char>(i), "ascend");
    }
    
    ofile.close();
    
    return 0;
}

int set_array(char* points, size_t arr_len, char value, string mode) {
   
    if(mode == "default") {
        for(size_t i = 0; i < arr_len; ++i) {
            points[i] = value;
        }
    } 
    else if(mode == "ascend") {
        for(size_t i = 0; i < arr_len; ++i) {
            points[i] = static_cast<char>(i);
        }
    }
    
    return 0;
}

