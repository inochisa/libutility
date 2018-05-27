
#ifndef __UTILITY_TRAIT_TYPE_PROPERTY_IS_VOLATILE__
#define __UTILITY_TRAIT_TYPE_PROPERTY_IS_VOLATILE__

#include<utility/trait/trait_helper.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace property
      {
        // is_volatile
        template<typename _T>
        struct is_volatile :
          public trait::false_type
        { };
        template<typename _T>
        struct is_volatile<_T volatile> :
          public trait::true_type
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_PROPERTY_IS_VOLATILE__
