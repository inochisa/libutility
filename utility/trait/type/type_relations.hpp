
#ifndef __UTILITY_TRAIT_TYPE_RELATIONS__
#define __UTILITY_TRAIT_TYPE_RELATIONS__

#include<utility/trait/type/releations/is_same.hpp>
#include<utility/trait/type/releations/is_convertible.hpp>
#include<utility/trait/type/releations/is_base_of.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace releations
      {

        // is_invocable(C++17)
        template<class Fn, class... ArgTypes>
        struct is_invocable;

        // is_invocable_r(C++17)
        template<class R, class Fn, class... ArgTypes>
        struct is_invocable_r;

        // is_nothrow_invocable(C++17)
        template<class Fn, class... ArgTypes>
        struct is_nothrow_invocable;

        // is_nothrow_invocable_r(C++17)
        template<class R, class Fn, class... ArgTypes>
        struct is_nothrow_invocable_r;

      }
    }
  }
}

#endif // ! __UTILITY_TRAIT_TYPE_RELATIONS__
