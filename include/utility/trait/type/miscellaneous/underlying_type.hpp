
#ifndef __UTILITY_TRAIT_TYPE_MISCELLANEOUS_UNDERLYING_TYPE__
#define __UTILITY_TRAIT_TYPE_MISCELLANEOUS_UNDERLYING_TYPE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/config/trait_config.hpp>

#if __utility_has_underlying_type

#include<utility/trait/config/trait_config.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace miscellaneous
      {
        // underlying_type
        template<typename _T>
        struct underlying_type
        {
          typedef __utility_underlying_type(_T) type;
        };

        template<typename _T>
        using underlying_type_t = typename underlying_type<_T>::type;
      }
    }
  }
}

#endif // __utility_has_underlying_type

#include<utility/trait/config/trait_undef.hpp>

#endif // __UTILITY_TRAIT_TYPE_MISCELLANEOUS_UNDERLYING_TYPE__
