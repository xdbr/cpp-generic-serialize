#ifndef CONCEPTS_HPP
#define CONCEPTS_HPP

#include <type_traits>
#include <experimental/type_traits>

namespace util::serialize::binary {
  template<typename T> concept bool Fundamental() { return std::experimental::is_fundamental_v<T>; }
  template<typename T> concept bool Array()       { return std::experimental::is_array_v<T>; }
  template<typename T> concept bool Pair()        { return requires(T t) { t.first; t.second; }; }
  template<typename T> concept bool Iterable()    { 
    return requires(T t) {
      t.begin();
      t.end();
      t.size();
    };
  }
  template<typename T>
  requires Iterable<T>()
  concept bool AssociativeContainer() { return requires(T t) { t.value_comp(); }; }
}

#endif
