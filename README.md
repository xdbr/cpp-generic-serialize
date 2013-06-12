cpp-generic-serialize
=====================

C++11 Header-only generic binary-serialization for arbriray types (and nested containers)

Description
----------- 

Header-only library to ease binary serialization.

Examples
--------

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

Usage
-----

* `include` the header file
* Compile your executable/library with `-std=c++11`
    * (this is a C++11-only header, making heavy use of template meta-programming and C++11-type_traits)

Tests
-----

Run `rake clobber; rake`

References
----------

A lot of inspiration (and a mediocre-sized bit of code) was taken from http://flamingdangerzone.com/. This is an absolutely worth reading, and very enlightening. Great work!

License
-------

WTFPL
