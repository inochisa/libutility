
#ifndef __UTILITY_MISCELLANEOUS_IGNORE_UNUSED__
#define __UTILITY_MISCELLANEOUS_IGNORE_UNUSED__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace miscellaneous
  {
    template<typename... Ts>
    UTILITY_ALWAYS_INLINE __UTILITY_CPP14_CONSTEXPR__
    inline void ignore_unused()
    { }
    template<typename... Ts>
    UTILITY_ALWAYS_INLINE __UTILITY_CPP14_CONSTEXPR__
    inline void ignore_unused(const Ts& ...)
    { }
  }
}

#endif // ! __UTILITY_MISCELLANEOUS_IGNORE_UNUSED__
