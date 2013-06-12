#ifndef IS_CONTAINER_HPP
#define IS_CONTAINER_HPP

#include <type_traits>

namespace util {

// most parts stolen from:
// http://flamingdangerzone.com/

// template <bool If, typename Then, typename Else>
// using Conditional = typename std::conditional<If, Then, Else>::type;

template <typename If, typename Then, typename Else>
using Conditional = typename std::conditional<If::value, Then, Else>::type;

template <bool B, typename...>
struct dependent_bool_type : std::integral_constant<bool, B> {};
// and an alias, just for kicks :)
template <bool B, typename... T>
using Bool = typename dependent_bool_type<B, T...>::type;


// Meta-logical negation
template <typename T>
using Not = Bool<!T::value>;

// Meta-logical disjunction
template <typename... T>
struct any : Bool<false> {};
template <typename Head, typename... Tail>
struct any<Head, Tail...> : Conditional<Head, Bool<true>, any<Tail...> > {};

// Meta-logical conjunction
template <typename... T>
struct all : Bool<true> {};
template <typename Head, typename... Tail>
struct all<Head, Tail...> : Conditional<Head, all<Tail...>, Bool<false>> {};

// template <typename T>
// using Unqualified = RemoveCv<RemoveReference<T>>;
//
// template <typename T>
// using Bare = RemoveCv<RemoveReference<T>>;


template <typename T>
struct identity { using type = T; };

// template <typename T>
// struct unwrap_reference
// : identity<T> {};
//
// template <typename T>
// struct unwrap_reference<std::reference_wrapper<T>>
// : identity<T&> {};

// template <typename T>
// struct decay_reference : unwrap_reference<Decay<T>> {};
// template <typename T>
// using DecayReference = Invoke<decay_reference<T>>;

template <typename T>
using Invoke = typename T::type;

template <typename T>
struct unwrap_reference
: identity<T> {};

template <typename T>
struct unwrap_reference<std::reference_wrapper<T>>
: identity<T&> {};

template <typename T>
struct decay_reference : unwrap_reference<std::decay<T>> {};
template <typename T>
using DecayReference = Invoke<decay_reference<T>>;

template <typename T>
using UnderlyingType = Invoke<std::underlying_type<T>>;

template <typename T>
struct remove_reference : unwrap_reference<std::remove_reference<T>> {};
template <typename T>
using RemoveReference = Invoke<remove_reference<T>>;

template <typename T>
struct remove_cv : unwrap_reference<std::remove_cv<T>> {};
template <typename T>
using RemoveCv = Invoke<remove_cv<T>>;

template <typename T>
using Unqualified = RemoveCv<RemoveReference<T>>;



namespace detail { enum class enabler {}; }

template <typename... Condition>
using EnableIf = typename std::enable_if<all<Condition...>::value, detail::enabler>::type;

template<typename A, A, A>              struct is_of_type  { typedef void type; };
template<typename A, A, A, typename B>  struct is_of_type2 { typedef void type; };

template<typename Container, typename = void>
struct is_container : std::false_type { };

template<typename Container, typename = void>
struct is_associative_container : std::false_type { };

template<typename Container, typename = void>
struct is_non_associative_container : std::false_type { };

// Include this if you want STL-Containers only
// template<>
// struct is_container<std::string> : std::false_type { };


template<typename C>
struct is_container<C,
    typename is_of_type<
        typename C::const_iterator(C::*)() const,
        &C::begin,
        &C::end
    >::type
> : std::is_class<C> { };


template<typename C>
struct is_associative_container<C,
    typename is_of_type2<    // this makes it associative #1
        typename C::const_iterator(C::*)() const,
        &C::begin,
        &C::end,
        typename C::mapped_type // this makes it associative #1
    >::type
>
: std::is_class<C> { };


template<typename C>
struct is_non_associative_container<C,
    util::Conditional<
        all< is_container<C>, util::Not<is_associative_container<C>> >,
        void,
        Bool<true>
    >
>
: std::is_class<C> { };

} /* end of namespace util */

#endif /* end of include guard: IS_CONTAINER_HPP */
