# cpp-generic-serialize

C++17 header-only generic binary-serialization for arbitrary STL-containers


## Examples
    
    using namespace std;
    using namespace usb = util::serialize::binary;
    
    ofstream   os{fn, ios::out | ios::binary};
    
    list<vector<map<string, unsigned>>> foobar{{{{"foo", 5}, {"bar", 42}}}};
    usb::save(ofstream_binary, foobar);
    
    // a little later... load the container back in:
    ifstream   is{fn, ios::out | ios::binary};
    
    auto barbaz = usb::load<list<vector<map<string, unsigned>>>>( is );

See the test cases for more examples.

## Usage

* `#include` the header file
* Compile using `-std=c++17 -fconcepts`

## Tests

Run `make`

## License

WTFPL
