
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
        struct is_same : public ::utility::trait::false_type
        { };
        template<typename _T>
        struct is_same<_T, _T> : public ::utility::trait::true_type
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_RELEATIONS_IS_SAME__
