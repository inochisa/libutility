
#ifndef __UTILITY_TRAIT_TYPE_PROPERTY_IS_CONST__
#define __UTILITY_TRAIT_TYPE_PROPERTY_IS_CONST__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace property
      {
        // is_const
        template<typename _T>
        struct is_const : public utility::trait::false_type
        { };
        template<typename _T>
        struct is_const<_T const> : public utility::trait::true_type
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_PROPERTY_IS_CONST__
