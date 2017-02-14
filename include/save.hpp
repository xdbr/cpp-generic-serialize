#ifndef SAVE_HPP
#define SAVE_HPP

#include "concepts.hpp"
#include <fstream> // write

namespace util::serialize::binary {
  template<Pair T>        void save(std::ofstream&, T);
  template<Array T>       void save(std::ofstream&, T);
  template<Iterable T>    void save(std::ofstream&, T);
  template<Fundamental T> void save(std::ofstream&, T);

  template<Pair T> 
  void save(std::ofstream & os, T t) {
    save(os, t.first);
    save(os, t.second);
  }
  
  template<Array T>
  void save(std::ofstream & os, T t) {
    unsigned size = t.size();
    save(os, size);
  }

  template<Iterable T>
  void save(std::ofstream & os, T t) {
    unsigned size = t.size();
    save(os, size);

    for (const auto& it: t) save(os, it);
  }

  template<Fundamental T> 
  void save(std::ofstream & os, T t) {
    os.write(reinterpret_cast<const char*>(&t), sizeof(t));
  }
}

#endif
