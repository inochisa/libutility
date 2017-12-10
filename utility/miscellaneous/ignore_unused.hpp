
#ifndef __UTILITY_MISCELLANEOUS_IGNORE_UNUSED__
#define __UTILITY_MISCELLANEOUS_IGNORE_UNUSED__

#include<utility/config/utility_config.hpp>

namespace utility
{
  namespace miscellaneous
  {
    template<typename... Ts>
    inline void ignore_unused(...)
    { }
  }
}

#endif // ! __UTILITY_MISCELLANEOUS_IGNORE_UNUSED__
