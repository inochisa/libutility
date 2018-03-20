
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_SCALAR__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_SCALAR__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/categories/is_arithmetic.hpp>
#include<utility/trait/type/categories/is_member_pointer.hpp>
#include<utility/trait/type/categories/is_pointer.hpp>
#include<utility/trait/type/categories/is_null_pointer.hpp>
#include<utility/trait/type/categories/is_enum.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace categories
      {
        // is_scalar
        template<typename _T>
        struct is_scalar :
          public utility::trait::integral_constant<bool,
            is_arithmetic<_T>::value     ||
            is_member_pointer<_T>::value ||
            is_pointer<_T>::value        ||
            is_null_pointer<_T>::value   ||
            is_enum<_T>::value>
        { };
        template<>
        struct is_scalar<utility::trait::nullptr_t> :
          public utility::trait::true_type
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_CATEGORIES_IS_SCALAR__
