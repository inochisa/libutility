
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_NOHTROW_DEFAULT_CONSTRUCTIBLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_NOHTROW_DEFAULT_CONSTRUCTIBLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/features/is_nothrow_constructible.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_nothrow_default_constructible
        template<typename _T>
        struct is_nothrow_default_constructible :
          public trait::type::features::is_nothrow_constructible<_T>
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_FEATURES_IS_NOHTROW_DEFAULT_CONSTRUCTIBLE__
