
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_MEMBER_OBJECT_POINTER__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_MEMBER_OBJECT_POINTER__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/categories/is_member_pointer.hpp>
#include<utility/trait/type/categories/is_member_function_pointer.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace categories
      {
        // is_member_object_pointer
        template<typename _T>
        struct is_member_object_pointer :
          public utility::trait::integral_constant<bool,
            is_member_pointer<_T>::value           &&
            !is_member_function_pointer<_T>::value>
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_CATEGORIES_IS_MEMBER_OBJECT_POINTER__
