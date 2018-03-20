
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_COPYABLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_COPYABLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/features/is_copy_constructible.hpp>
#include<utility/trait/type/features/is_copy_assignable.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_copyable
        template<typename _T>
        struct is_copyable :
          public utility::trait::integral_constant<bool,
            utility::trait::type::features::is_copy_constructible<_T>::value &&
            utility::trait::type::features::is_copy_assignable<_T>::value>
        { };
      }
    }
  }
}

#endif // ! __UTILITY_TRAIT_TYPE_FEATURES_IS_COPYABLE__
