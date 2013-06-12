/*

    test_binary.cpp

    Test cases for cpp-generic-serialize
*/

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>

#include "binary.hpp"

int main() {

    std::ofstream   map1_file_o("map1_file.bin", std::ios::out | std::ios::binary);
    std::map<int, std::string>  map1_load,
                                map1_save = { {1, "foo"}, {2, "bar"}};

    util::serialize::binary::save(map1_file_o, map1_save);
    map1_file_o.close();
    
    std::ifstream   map1_file_i("map1_file.bin", std::ios::in | std::ios::binary);
    util::serialize::binary::load(map1_file_i, map1_load);
    
    assert(map1_save == map1_load);
    
    std::cout << "All tests run successful." << std::endl;
    return 0;
}