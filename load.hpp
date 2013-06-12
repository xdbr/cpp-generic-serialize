#ifndef LOAD_HPP
#define LOAD_HPP

#include "binary.hpp"
#include "type_traits/extended/is_container.hpp"

#include <string>
#include <utility> // std::pair
#include <fstream> // read

using namespace util;

namespace util { namespace serialize { namespace binary {

    template <typename T, EnableIfFundamental            <T>...> T load(std::ifstream&, T&);
    template <typename T, EnableIfAssociativeContainer   <T>...> T load(std::ifstream&, T&);
    template <typename T, EnableIfNonAssociativeContainer<T>...> T load(std::ifstream&, T&);
    template <typename T, EnableIfArray                  <T>...> T load(std::ifstream&, T&);
    // template <typename T, EnableIfString                 <T>...> T load(std::ifstream&, T&);
    template<class K, class V>                      std::pair<K,V> load(std::ifstream&, std::pair<K,V>&);

    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    /*                  L  O  A  D                                               */
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    template <typename T, EnableIfFundamental<T>...>
    T
    load(std::ifstream & is, T & t) {
//_vniHere;

        is.read(reinterpret_cast<char*>(&t), /*static_cast<(std::streamsize)*/sizeof(t) );
// _vniMsg("-- load fundamental, size = " << sizeof(t) << " / t = " << t);
        return t;
    }


    template <typename T, EnableIfAssociativeContainer<T>...>
    T
    load(std::ifstream & is, T & t) {
//_vniHere;

        unsigned size = 0;
        load(is, size);

// _vniMsg("-- load AssociativeContainer, size = " << size);

        std::insert_iterator< T > insert_it(t, t.begin());
//_vniHere;

        for (unsigned i = 0; i < size; i++) {
            util::Invoke<util::DecayReference<typename T::key_type   >> e;
            util::Invoke<util::DecayReference<typename T::mapped_type>> f;
//_vniHere;

            e = load(is, e);
//_vniHere;
            f = load(is, f);
//_vniHere;
            *insert_it++ = std::make_pair(e,f);
//_vniHere;
        }
//_vniHere;
        return t;
    }


    template <typename T, EnableIfNonAssociativeContainer<T>...>
    T
    load(std::ifstream & is, T & t) {
//_vniHere;
        unsigned size = 0;
        load(is, size);

// _vniMsg("-- load NonAssociativeContainer, size = " << size);
        std::insert_iterator< T > insert_it(t, t.begin());
//_vniHere;
        for (unsigned i = 0; i < size; i++) {
//_vniHere;
            util::Invoke<util::DecayReference<typename T::value_type>> e;
//_vniHere;
            *insert_it++ = load(is, e);
        }

        return t;
    }

    template <typename T, EnableIfArray<T>...>
    T
    load(std::ifstream & is, T & t) {
//_vniHere;
        is.read(reinterpret_cast<char*>(&t), /*static_cast<(std::streamsize)*/sizeof(t) );
//_vniHere;
        return t;
    }


//     template <typename T, EnableIfString<T>...>
//     T
//     load(std::ifstream & is, T & t) {
// //_vniHere;
//         size_t  size = 0;
//         // is.read(reinterpret_cast<char *>(&size), sizeof(size_t));
//         load(is, size);
// _vniVar(size);
//         char * buffer = new char[size];
// //_vniHere;
//         is.read(reinterpret_cast<char *>(&buffer), (unsigned)size);
//         // buffer[size] = 'X';
//         std::cout << "BUFFER::: " << buffer << std::endl;
// _vniVar(buffer);
//         t = std::string(buffer, (unsigned)size);
//         std::cout << "T::: " << t << std::endl;
// _vniVar(t);
//         return t;
//     }

    template<class K, class V>
    std::pair<K,V>
    load(std::ifstream & is, std::pair<K,V> & t) {

        K key = load<K>(is, key);
        // K key = load(is, key);
        V val = load(is, val);

        std::pair<K,V>  temp(key, val);

        t = std::pair<typename std::remove_cv<K>::type,V>(key, val);

        return t;
    }

} } } /* namespace util::serialize::binary */

#endif /* end of include guard: LOAD_HPP */
