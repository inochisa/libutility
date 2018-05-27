
#ifndef __UTILITY_TRAIT_TYPE_CATEGORIES_IS_ARRAY__
#define __UTILITY_TRAIT_TYPE_CATEGORIES_IS_ARRAY__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace categories
      {
        // is_array
        template<typename _T>
        struct is_array : public trait::false_type
        { };
        template<typename _T>
        struct is_array<_T[]> : public trait::true_type
        { };
        template<typename _T, trait::size_t size>
        struct is_array<_T[size]> : public trait::true_type
        { };

      }
    }
  }
}

#endif // ! __UTILITY_TRAIT_TYPE_CATEGORIES_IS_ARRAY__
