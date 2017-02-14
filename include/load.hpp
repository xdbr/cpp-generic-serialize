#ifndef LOAD_HPP
#define LOAD_HPP

#include "concepts.hpp"
#include <utility> // std::pair
#include <fstream> // read

namespace util::serialize::binary {

  /* declarations */
  template <Fundamental T> T load(std::ifstream&);
  template <Array T>       T load(std::ifstream&);
  template <Pair T>        T load(std::ifstream&);
  template <typename T> requires Iterable<T>() && AssociativeContainer<T>() T load(std::ifstream&);
  template <typename T> requires Iterable<T>() && !AssociativeContainer<T>() T load(std::ifstream&);

  template <Fundamental T> T load(std::ifstream&, T&);
  template <Array T>       T load(std::ifstream&, T&);
  template <Pair T>        T load(std::ifstream&, T&);
  template <typename T> requires Iterable<T>() && AssociativeContainer<T>() T load(std::ifstream&, T&);
  template <typename T> requires Iterable<T>() && !AssociativeContainer<T>() T load(std::ifstream&, T&);

  /* implementations */
  template <Fundamental T> T load(std::ifstream& in) {T t; return load(in, t); }
  template <Array T>       T load(std::ifstream& in) {T t; return load(in, t); }
  template <Pair T>        T load(std::ifstream& in) {T t; return load(in, t); }
  template <typename T> requires Iterable<T>() && AssociativeContainer<T>() T load(std::ifstream& in) {T t; return load(in, t); }
  template <typename T> requires Iterable<T>() && !AssociativeContainer<T>() T load(std::ifstream& in) {T t; return load(in, t); }


  template <Fundamental T>
  T load(std::ifstream & is, T & t) {
    is.read(reinterpret_cast<char*>(&t), /*static_cast<(std::streamsize)*/sizeof(t) );
    return t;
  }


  template<Array T>
  T load(std::ifstream & is, T & t) {
    is.read(reinterpret_cast<char*>(&t), /*static_cast<(std::streamsize)*/sizeof(t) );
    return t;
  }


  template<Pair T>
  T load(std::ifstream & is, T & t) {
    using key_type   = typename std::decay<typename T::first_type>::type;
    using value_type = typename T::second_type;
    auto key = load<key_type>(is);
    auto val = load<value_type>(is);
    return std::make_pair(key, val);
  }


  template<typename T>
  requires Iterable<T>() && AssociativeContainer<T>()
  T load(std::ifstream & is, T & t) {
    using key_type    = typename std::decay<typename T::key_type>::type;
    using mapped_type = typename std::decay<typename T::mapped_type>::type;

    unsigned size = 0;
    load(is, size);

    std::insert_iterator< T > insert_it(t, t.begin());

    for (unsigned i = 0; i < size; i++) {
      auto k = load<key_type>(is);
      auto v = load<mapped_type>(is);

      *insert_it++ = std::make_pair(k,v);
    }
    return t;
  }


  template<typename T>
  requires Iterable<T>() && !AssociativeContainer<T>()
  T load(std::ifstream & is, T & t) {
    unsigned size = 0;
    load(is, size);

    std::insert_iterator<T> insert_it(t, t.begin()); 

    for (unsigned i = 0; i < size; i++)
      *insert_it++ = load<typename T::value_type>(is);

    return t;
  }
}

#endif
