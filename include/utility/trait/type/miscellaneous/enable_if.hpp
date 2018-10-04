
#ifndef __UTILITY_TRAIT_TYPE_MISCELLANEOUS_ENABLE_IF__
#define __UTILITY_TRAIT_TYPE_MISCELLANEOUS_ENABLE_IF__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace miscellaneous
      {
        // enable_if
        template<bool _B, typename _T = void>
        struct enable_if
        { };
        template<typename _T>
        struct enable_if<true, _T>
        { typedef _T type;};

        template<bool _B, typename _T = void>
        using enable_if_t = typename enable_if<_B, _T>::type;
      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_MISCELLANEOUS_ENABLE_IF__
