cpp-generic-serialize
=====================

C++11 Header-only generic binary-serialization for arbriray types (and nested containers)

Description
----------- 

Header-only library to ease binary serialization.

Examples
--------

Essentially, these lines should sum up the purpose of this library:

    // open ofstream as binary ...
    // save arbitraty container or fundamental type to it:
    list<vector<map< string, unsigned >>> foobar;
    save(ofstream_binary, foobar);
    
    // a little later... load the container back in:
    
    auto barbaz = load< list<vector<map< string, unsigned >>> >( ifstream_binary );

See the test cases for more examples.

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
