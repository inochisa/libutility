
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_FUNDAMENTAL__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_FUNDAMENTAL__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/categories/is_void.hpp>
#include<utility/trait/type/categories/is_arithmetic.hpp>
#include<utility/trait/type/categories/is_null_pointer.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace categories
      {
        // is_fundamental
        template<typename _T>
        struct is_fundamental :
          public trait::integral_constant<bool,
            is_void<_T>::value       ||
            is_arithmetic<_T>::value ||
            is_null_pointer<_T>::value>
        { };

#if !defined(__UTILITY_NO_CPP14__)
        template<typename _T>
        constexpr bool is_fundamental_v = is_fundamental<_T>::value;
#endif

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_CATEGORIES_IS_FUNDAMENTAL__
