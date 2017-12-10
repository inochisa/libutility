
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_LVALUE_REFERENCE__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_LVALUE_REFERENCE__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace categories
      {
        // is_lvalue_reference
        template<typename _T>
        struct is_lvalue_reference :
          public ::utility::trait::false_type
        { };
        template<typename _T>
        struct is_lvalue_reference<_T&> :
          public ::utility::trait::true_type
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_CATEGORIES_IS_LVALUE_REFERENCE__
