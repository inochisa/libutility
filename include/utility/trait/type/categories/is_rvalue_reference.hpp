
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_RVALUE_REFERENCE__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_RVALUE_REFERENCE__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace categories
      {
        // is_rvalue_reference
        template<typename _T>
        struct is_rvalue_reference :
          public trait::false_type
        { };
        template<typename _T>
        struct is_rvalue_reference<_T&&> :
          public trait::true_type
        { };

#if !defined(__UTILITY_NO_CPP14__)
        template<typename _T>
        constexpr bool is_rvalue_reference_v = is_rvalue_reference<_T>::value;
#endif

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_CATEGORIES_IS_RVALUE_REFERENCE__
