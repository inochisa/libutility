
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_OBJECT__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_OBJECT__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/categories/is_scalar.hpp>
#include<utility/trait/type/categories/is_array.hpp>
#include<utility/trait/type/categories/is_union.hpp>
#include<utility/trait/type/categories/is_class.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace categories
      {
        // is_object
        template<typename _T>
        struct is_object :
          public trait::integral_constant<bool,
            is_scalar<_T>::value ||
            is_array<_T>::value  ||
            is_union<_T>::value  ||
            is_class<_T>::value>
        { };

#if !defined(__UTILITY_NO_CPP14__)
        template<typename _T>
        constexpr bool is_object_v = is_object<_T>::value;
#endif

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_CATEGORIES_IS_OBJECT__
