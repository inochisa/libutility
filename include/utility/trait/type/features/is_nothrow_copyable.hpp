
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_COPYABLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_COPYABLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/features/is_nothrow_copy_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_copy_assignable.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_nothrow_copyable
        template<typename _T>
        struct is_nothrow_copyable :
          public trait::integral_constant<bool,
            trait::type::features::is_nothrow_copy_constructible<_T>::value &&
            trait::type::features::is_nothrow_copy_assignable<_T>::value>
        { };
      }
    }
  }
}

#endif // ! __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_COPYABLE__
