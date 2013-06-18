#ifndef LOAD_HPP
#define LOAD_HPP

#include "binary.hpp"
#include "type_traits/extended/is_container.hpp"

#include <string>
#include <utility> // std::pair
#include <fstream> // read

using namespace util;

namespace util { namespace serialize { namespace binary {

 // template <typename T, EnableIfString                 <T>...> T load(std::ifstream&, T&);
    template <typename T, EnableIfFundamental            <T>...> T load(std::ifstream&);
    template <typename T, EnableIfAssociativeContainer   <T>...> T load(std::ifstream&);
    template <typename T, EnableIfNonAssociativeContainer<T>...> T load(std::ifstream&);
    template <typename T, EnableIfArray                  <T>...> T load(std::ifstream&);
    template<class K, class V>                      std::pair<K,V> load(std::ifstream&);

 // template <typename T, EnableIfString                 <T>...> T load(std::ifstream&, T&);
    template <typename T, EnableIfFundamental            <T>...> T load(std::ifstream&, T&);
    template <typename T, EnableIfAssociativeContainer   <T>...> T load(std::ifstream&, T&);
    template <typename T, EnableIfNonAssociativeContainer<T>...> T load(std::ifstream&, T&);
    template <typename T, EnableIfArray                  <T>...> T load(std::ifstream&, T&);
    template<class K, class V>                      std::pair<K,V> load(std::ifstream&, std::pair<K,V>&);


    template <typename T, EnableIfFundamental <T>...>
    T load(std::ifstream& in) {
        T t;
        return load(in, t);
    }
    
    template <typename T, EnableIfAssociativeContainer <T>...>
    T load(std::ifstream& in) {
        T t;
        return load(in, t);
    }
    
    template <typename T, EnableIfNonAssociativeContainer<T>...>
    T load(std::ifstream& in) {
        T t;
        return load(in, t);
    }
    
    template <typename T, EnableIfArray <T>...>
    T load(std::ifstream& in) {
        T t;
        return load(in, t);
    }
    
    // template <typename T, EnableIfString <T>...>
    // T load(std::ifstream&, T& in) {
    //     T t;
    //     return load(in, t);
    // }

    template<class K, class V>                      std::pair<K,V> load(std::ifstream& in) {
        std::pair<K,V> t;
        return load(in, t);
    }


    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
    /*                  L  O  A  D                                               */
    /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

    template <typename T, EnableIfFundamental<T>...>
    T
    load(std::ifstream & is, T & t) {
        is.read(reinterpret_cast<char*>(&t), /*static_cast<(std::streamsize)*/sizeof(t) );
        return t;
    }


    template <typename T, EnableIfAssociativeContainer<T>...>
    T
    load(std::ifstream & is, T & t) {
        unsigned size = 0;
        load(is, size);

        std::insert_iterator< T > insert_it(t, t.begin());

        for (unsigned i = 0; i < size; i++) {
            util::Invoke<util::DecayReference<typename T::key_type   >> e;
            util::Invoke<util::DecayReference<typename T::mapped_type>> f;

            e = load(is, e);
            f = load(is, f);

            *insert_it++ = std::make_pair(e,f);
        }
        return t;
    }


    template <typename T, EnableIfNonAssociativeContainer<T>...>
    T
    load(std::ifstream & is, T & t) {
        unsigned size = 0;
        load(is, size);

        std::insert_iterator< T > insert_it(t, t.begin());

        for (unsigned i = 0; i < size; i++) {
            util::Invoke<util::DecayReference<typename T::value_type>> e;
            *insert_it++ = load(is, e);
        }

        return t;
    }

    template <typename T, EnableIfArray<T>...>
    T
    load(std::ifstream & is, T & t) {
        is.read(reinterpret_cast<char*>(&t), /*static_cast<(std::streamsize)*/sizeof(t) );
        return t;
    }


    // template <typename T, EnableIfString<T>...>
    // T
    // load(std::ifstream & is, T & t) {
    //     size_t  size = 0;
    //     // is.read(reinterpret_cast<char *>(&size), sizeof(size_t));
    //     load(is, size);
    //     char * buffer = new char[size];
    //     is.read(reinterpret_cast<char *>(&buffer), (unsigned)size);
    //     t = std::string(buffer, (unsigned)size);
    //     return t;
    // }

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
