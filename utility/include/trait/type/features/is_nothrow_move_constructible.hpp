
#ifndef __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_MOVE_CONSTRUCTIBLE__
#define __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_MOVE_CONSTRUCTIBLE__

#include<utility/trait/trait_helper.hpp>
#include<utility/trait/type/transform/add_reference.hpp>
#include<utility/trait/type/features/is_nothrow_constructible.hpp>

namespace utility
{
  namespace trait
  {
    namespace type
    {
      namespace features
      {
        // is_nothrow_move_constructible
        template<typename _T>
        struct is_nothrow_move_constructible : public
          trait::type::features::is_nothrow_constructible<_T,
            typename
            trait::type::transform::add_rvalue_reference<_T>::type>
        { };

      }
    }
  }
}

#endif // __UTILITY_TRAIT_TYPE_FEATURES_IS_NOTHROW_COPY_CONSTRUCTIBLE__
