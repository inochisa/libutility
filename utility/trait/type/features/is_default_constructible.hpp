
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_DEFAULT_CONSTRUCTIBLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_DEFAULT_CONSTRUCTIBLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/features/is_constructible.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_default_constructible
        template<typename _T>
        struct is_default_constructible : public is_constructible<_T>
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_FEATURES_IS_DEFAULT_CONSTRUCTIBLE__
