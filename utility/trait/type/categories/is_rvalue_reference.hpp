
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
          public ::utility::trait::false_type
        { };
        template<typename _T>
        struct is_rvalue_reference<_T&&> :
          public ::utility::trait::true_type
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_CATEGORIES_IS_RVALUE_REFERENCE__
