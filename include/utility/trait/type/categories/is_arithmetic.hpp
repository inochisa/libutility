
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_ARITHMETIC__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_ARITHMETIC__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/categories/is_integral.hpp>
#include<utility/trait/type/categories/is_floating_point.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace categories
      {
        // is_arithmetic
        template<typename _T>
        struct is_arithmetic :
          public trait::integral_constant<bool,
            is_integral<_T>::value || is_floating_point<_T>::value>
        { };

#if !defined(__UTILITY_NO_CPP14__)
        template<typename _T>
        constexpr bool is_arithmetic_v = is_arithmetic<_T>::value;
#endif

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_CATEGORIES_IS_ARITHMETIC__
