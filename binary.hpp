#include "type_traits/extended/is_container.hpp"

#include "save.hpp"
#include "load.hpp"
#include "skip.hpp"

#include <string>

namespace util { namespace serialize { namespace binary {
    
    template <typename Type> using EnableIfContainer                = util::EnableIf<util::is_container                 <util::Invoke<util::DecayReference<Type>>>>;
    template <typename Type> using EnableIfAssociativeContainer     = util::EnableIf<util::is_associative_container     <util::Invoke<util::DecayReference<Type>>>>;
    template <typename Type> using EnableIfNonAssociativeContainer  = util::EnableIf<util::is_non_associative_container <util::Invoke<util::DecayReference<Type>>>>;
    template <typename Type> using EnableIfArithmetic               = util::EnableIf<util::Invoke<std::is_arithmetic    <util::Invoke<util::DecayReference<Type>>>>>;
    template <typename Type> using EnableIfFundamental              = util::EnableIf<util::Invoke<std::is_fundamental   <util::Invoke<util::DecayReference<Type>>>>>;
    template <typename Type> using EnableIfArray                    = util::EnableIf<util::Invoke<std::is_array         <util::Invoke<util::DecayReference<Type>>>>>;
    template <typename Type> using EnableIfString                   = typename std::enable_if<std::is_same<std::string,  util::Invoke<util::DecayReference<Type>>>::value>::type;
    
} } } /* namespace util::serialize::binary */