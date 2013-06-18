#ifndef SAVE_HPP
#define SAVE_HPP

#include "binary.hpp"
#include "type_traits/extended/is_container.hpp"

#include <utility> // std::pair
#include <fstream> // write

// using namespace util;

namespace util { namespace serialize { namespace binary {

    // forward declarations
    template <typename T, EnableIfFundamental<T>...> T save(std::ofstream&, T);
    template <typename T, EnableIfContainer  <T>...> T save(std::ofstream&, T);
    template <typename T, EnableIfArray      <T>...> T save(std::ofstream&, T);
    // template <typename T, EnableIfString     <T>...> T save(std::ofstream&, T);
    template<class K, class V>          std::pair<K,V> save(std::ofstream&, std::pair<K,V>);



    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    /*                  S  A  V  E                                               */
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    template <typename T, EnableIfFundamental<T>...>
    T
    save(std::ofstream & os, T t) {
        os.write(reinterpret_cast<const char*>(&t), sizeof(t));
        return t;
    }

    template <typename T, EnableIfContainer<T>...>
    T
    save(std::ofstream & os, T t) {
        unsigned size = t.size();
        save(os, size);

        for (auto it = begin(t); it != end(t); ++it) {
            save(os, *it);
        }
        return t;
    }

    template <typename T, EnableIfArray<T>...>
    T
    save(std::ofstream & os, T t) {
        unsigned size = t.size();
        save(os, size);

        return t;
    }

    // template <typename T, EnableIfString<T>...>
    // T
    // save(std::ofstream & os, T t) {
    //     size_t       size = t.size() + 1;
    //     // os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    //     save(os, size);
    //     const char * data = t.data();
    //     os.write(reinterpret_cast<const char*>(&data), (unsigned)size);
    //
    //     return t;
    // }

    template<class K, class V>
    std::pair<K,V>
    save(std::ofstream & os, std::pair<K,V> t) {

        save(os, t.first);
        save(os, t.second);

        return t;
    }

} } } /* namespace util::serialize::binary */

#endif /* end of include guard: SAVE_HPP */
