
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_MOVEABLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_MOVEABLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/features/is_nothrow_move_constructible.hpp>
#include<utility/trait/type/features/is_nothrow_move_assignable.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_nothrow_moveable
        template<typename _T>
        struct is_nothrow_moveable :
          public trait::integral_constant<bool,
            trait::type::features::is_nothrow_move_constructible<_T>::value &&
            trait::type::features::is_nothrow_move_assignable<_T>::value>
        { };
      }
    }
  }
}

#endif // ! __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_MOVEABLE__
