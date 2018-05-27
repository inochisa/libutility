
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_REFERENCE__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_REFERENCE__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace categories
      {
        // is_reference
        template<typename _T>
        struct is_reference : public trait::false_type
        { };
        template<typename _T>
        struct is_reference<_T&> : public trait::true_type
        { };
        template<typename _T>
        struct is_reference<_T&&> : public trait::true_type
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_CATEGORIES_IS_REFERENCE__
