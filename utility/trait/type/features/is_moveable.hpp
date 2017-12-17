
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_MOVEABLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_MOVEABLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/features/is_move_constructible.hpp>
#include<utility/trait/type/features/is_move_assignable.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_moveable
        template<typename _T>
        struct is_moveable :
          public ::utility::trait::integral_constant<bool,
            ::utility::trait::type::features::is_move_constructible<_T>::value &&
            ::utility::trait::type::features::is_move_assignable<_T>::value>
        { };
      }
    }
  }
}

#endif // ! __UTILITY_TRAIT_TYPE_FEATURES_IS_MOVEABLE__
