#ifndef SKIP_HPP
#define SKIP_HPP

#include "binary.hpp"

namespace util::serialize::binary {
  template <typename T>
  void skip(std::ifstream & is) {
    load<T>(is); // throw-away but advance in file
  }
}

#endif
