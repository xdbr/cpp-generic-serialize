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
#include <list>

#include "binary.hpp"

int main() {

    namespace usb = util::serialize::binary;

    /* * *  Test 1  * * */
    std::ofstream   map1_file_o("map1_file.bin", std::ios::out | std::ios::binary);
    std::map<int, std::string>  map1_load,
                                map1_save = { {1, "foo"}, {2, "bar"}};

    util::serialize::binary::save(map1_file_o, map1_save);
    map1_file_o.close();
    
    std::ifstream   map1_file_i("map1_file.bin", std::ios::in | std::ios::binary);
    util::serialize::binary::load(map1_file_i, map1_load);
    
    assert(map1_save == map1_load);
    
    
    /* * *  Test 2  * * */
    std::list<unsigned int> list1_load,
                            list1_save = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    std::ofstream           list1_file_o("list1_file.bin", std::ios::out | std::ios::binary);

    usb::save(list1_file_o, list1_save);

    list1_file_o.close();

    
    std::ifstream           list1_file_i("list1_file.bin", std::ios::in | std::ios::binary);

    auto list1_l = usb::load< std::list<unsigned int> >(list1_file_i);
    
    assert(list1_l == list1_save);
    

    std::cout << "All tests run successful." << std::endl;
    return 0;
}