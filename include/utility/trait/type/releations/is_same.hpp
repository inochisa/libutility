
#ifndef __UTILITY_TRAIT_TYPE_RELEATIONS_IS_SAME__
#define __UTILITY_TRAIT_TYPE_RELEATIONS_IS_SAME__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace releations
      {
        // is_same
        template<typename _T1, typename _T2>
        struct is_same : public trait::false_type
        { };
        template<typename _T>
        struct is_same<_T, _T> : public trait::true_type
        { };

#if !defined(__UTILITY_NO_CPP14__)
        template<typename _T1, typename _T2>
        constexpr bool is_same_v = is_same<_T1, _T2>::value;
#endif

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_RELEATIONS_IS_SAME__
