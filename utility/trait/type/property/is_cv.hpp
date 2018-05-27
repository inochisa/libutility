
#ifndef __UTILITY_TRAIT_TYPE_PROPERTY_IS_CV__
#define __UTILITY_TRAIT_TYPE_PROPERTY_IS_CV__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/property/is_const.hpp>
#include<utility/trait/type/property/is_volatile.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace property
      {
        // is_cv
        template<typename _T>
        struct is_cv :
          public trait::false_type
        { };
        template<typename _T>
        struct is_cv<_T const volatile> :
          public trait::true_type
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_PROPERTY_IS_CV__
